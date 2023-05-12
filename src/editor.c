/* 
 * LIVSDiary
 * (C) 2022 Olivia May - olmay@tuta.io GPLv3+
 *
 * (LI)ghtweight (V)irtual (S)imple Diary
 *
 * A program that should make a directory in the user's home folder. 
 * And be able to store a diary on the user's hard drive. Maybe also
 * in memory too when it runs. It will be a command line program.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "converters.h"
#include "editor.h"
#include "filesystem.h"
#include "config.h"

void editor_help() {
    clear();
    printw("** LIVSDiary %s Editor Help **\n", VERSION);
    printw(":e [number]<enter>          open page [number]\n");
    printw(":h<enter>   :help<enter>    show this menu\n");
    printw(":n<enter>                   make new page\n");
    printw(":q<enter>                   quit editor\n");
    printw(":r<enter>                   remove newest page\n");
    printw(":w<enter>                   save changes\n");
    printw(":wq<enter>                  save and quit\n");
    printw("\n");
    printw("Press any key to go back to editing.\n");
    getch();
    clear();
}

CoordYX *get_stdscr_maxyx() {
    CoordYX *stdscr_maxyx = NULL;

    stdscr_maxyx = malloc(2 * sizeof(int));
    getmaxyx(stdscr, stdscr_maxyx->y, stdscr_maxyx->x);

    return stdscr_maxyx;
}

void editor_draw_command_line() {
    move(get_stdscr_maxyx()->y - 1, 0);
    addch(':');
}

void editor_enter() {
    initscr();
    cbreak();
    echo();

    editor_draw_command_line();
    move(0, 0);
}
void editor_exit() {
    endwin();
}

// CoordYX so it can pass ':e 2' for example
CoordYX editor_command_mode() {
    CoordYX cursor_coord;
    char ch;
    int i;
    char command_str[8];
    
    getyx(stdscr, cursor_coord.y, cursor_coord.x);
    move(get_stdscr_maxyx()->y - 1, 1);

    i = 0;
    while (true) {
        ch = getch();
        if (ch == '\n') {
            command_str[i] = '\0';
            move(get_stdscr_maxyx()->y - 1, 1);
            for (i = 1; i < get_stdscr_maxyx()->x; i++) addch(' ');
            move(cursor_coord.y, cursor_coord.x);
            break;
        }
        command_str[i] = ch;

        if (i != 7) i++;
    }

    CoordYX retval;
    retval.y = -1; retval.x = 0;
    
    if (strncmp(command_str, "q", 2) == 0) {
        retval.y = QUIT; retval.x = 0; return retval;
    }
    if (strncmp(command_str, "w", 2) == 0) {
        retval.y = WRITE; retval.x = 0; return retval;
    }
    if (strncmp(command_str, "wq", 3) == 0) {
        retval.y = WRITE_QUIT; retval.x = 0; return retval;
    }
    if (strncmp(command_str, "h", 2) == 0 ||
    strncmp(command_str, "help", 5) == 0) { retval.y = HELP; retval.x = 0; return retval;
    }
    if (strncmp(command_str, "n", 2) == 0) { retval.y = NEW_PAGE; retval.x = 0; return retval; 
    }
    if (strncmp(command_str, "r", 2) == 0) {
        retval.y = REMOVE_PAGE; retval.x = 0; return retval;
    }
    if (strncmp(command_str, "e", 1) == 0) { 
        retval.y = OPEN;
        char arg_str[7];
        int offset = 0;
        for (int i = 0; i < 7; i++) {
            if (command_str[i + 1] == ' ') offset+=1;
            else arg_str[i - offset] = command_str[i + 1];
        }
        if (check_input_is_int(arg_str)) {
			int arg_int = convert_to_int(arg_str);		

            if (arg_int <= (int)get_page_count()
            && arg_int >= 0) retval.x = arg_int;
		    else retval.x = get_page_count();
        }
		else retval.x = get_page_count();
        
        return retval;
    }
    
    return retval;
}

void editor_open_page(char *page_num_str) {
#define CLOSE_PAGE clear(); editor_draw_command_line(); move(0, 0); free(page_loc); free(editor_buffer);
#define WRITE_PAGE editor_buffer[editor_buffer_len] = '\0'; page_file = fopen(page_loc, "w"); fprintf(page_file, editor_buffer); fclose(page_file);

    
    char *page_loc = NULL; page_loc = loc_malloc();
    char *editor_buffer = NULL;
    FILE *page_file = NULL;
    char ch;
    int editor_buffer_len;
    CoordYX cursor_coord;

    strcpy(page_loc, get_diary_dir());
    strcat(page_loc, page_num_str);

    editor_buffer = get_file_contents(page_loc);
    printw(editor_buffer);

    while (true) {
        ch = getch();
        editor_buffer_len = strlen(editor_buffer);
        editor_buffer = realloc(editor_buffer,
        (editor_buffer_len + 2) * sizeof(char));

        if (ch == '\n') {
            getyx(stdscr, cursor_coord.y, cursor_coord.x);
            move(cursor_coord.y + 1, 0);
        }
        
        if (ch == '\x7F') { // backspace char "^?"
            clear();
            editor_draw_command_line();
            move(0, 0);
            if (editor_buffer[0] != '\0') { 
                editor_buffer[editor_buffer_len - 1] = '\0';
                printw(editor_buffer);
            }
        }
        else if (ch == ':') {
            printw("\b \b"); // dont show ':'
            CoordYX command_retval = editor_command_mode();
            switch (command_retval.y) {
                case QUIT: { editor_exit(); exit(0); } break;
                case WRITE: {
                    WRITE_PAGE
                } break;
                case WRITE_QUIT: {
                    WRITE_PAGE
                    editor_exit(); return;
                } break;
                case HELP: {
                    editor_help();
                    editor_draw_command_line();
                    move(0, 0);
                    printw(editor_buffer);
                } break;
                case NEW_PAGE: {
                    make_new_page();
                    WRITE_PAGE
                    CLOSE_PAGE
                    // recursion B)
                    editor_open_page(convert_to_char_array(get_page_count()));
                } break;
                case REMOVE_PAGE: {
                    WRITE_PAGE
                    remove_newest_page();
                    CLOSE_PAGE
                    editor_open_page(convert_to_char_array(get_page_count()));
                } break;
                case OPEN: {
                    WRITE_PAGE
                    CLOSE_PAGE
                    editor_open_page(convert_to_char_array(command_retval.x));
                } break;
            }
        }
        else {
            editor_buffer[editor_buffer_len] = ch;
            editor_buffer[editor_buffer_len + 1] = '\0';
        }
    }
}
