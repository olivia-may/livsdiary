/*
 * LIVSDiary - (LI)ghtweight (V)irtual (S)imple Diary
 * Copyright (C) 2022 Olivia May - olivia.may@tuta.io
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"
#include "converters.h"
#include "editor.h"
#include "filesystem.h"
#include "config.h"

char current_char;
int editor_buffer_len;
CoordYX cursoryx;
CoordYX stdscr_maxyx;
char *editor_buffer = NULL;

#define UPDATE_CURSORYX getyx(stdscr, cursoryx.y, cursoryx.x);

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

void editor_draw_command_line() {
    move(stdscr_maxyx.y - 1, 0);
    addch(':');
}

void editor_enter() {
    initscr();
    cbreak();
    echo();

    getmaxyx(stdscr, stdscr_maxyx.y, stdscr_maxyx.x);
    editor_draw_command_line();
    move(0, 0);
}
void editor_exit() {
    endwin();
}

void editor_backspace(char *buffer, int buffer_len) {
    printw("\b \b\b \b\b \b");
    if (buffer[0] != '\0') { 
        buffer[buffer_len - 1] = '\0';
    }
}

// CoordYX so it can pass ':e 2' for example
CoordYX editor_command_mode() {
    int i;
    char command_str[8];
    
    UPDATE_CURSORYX
    move(stdscr_maxyx.y - 1, 1);

    i = 0;
    while (true) {
        current_char = getch();
        if (current_char == '\n') {
            command_str[i] = '\0';
            move(stdscr_maxyx.y - 1, 1);
            for (i = 1; i < stdscr_maxyx.x; i++) addch(' ');
            move(cursoryx.y, cursoryx.x);
            break;
        }
        if (current_char == '\x7F') // backspace char "^?"
        editor_backspace(command_str, strlen(command_str));
        command_str[i] = current_char;

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
        if (check_input_is_unsigned_int(arg_str)) {
            int arg_int = convert_to_unsigned_int(arg_str);		
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
#define CLOSE_PAGE clear(); editor_draw_command_line(); move(0, 0); free(get_page_loc(page_num_str)); free(editor_buffer); free(page_loc);
#define WRITE_PAGE editor_buffer[editor_buffer_len] = '\0'; page_file = fopen(get_page_loc(page_num_str), "w"); fprintf(page_file, editor_buffer); fclose(page_file);
    
    FILE *page_file = NULL;
    char *page_loc = NULL;

    page_loc = get_page_loc(page_num_str);
    editor_buffer = get_file_contents(page_loc);
    printw(editor_buffer);

    while (true) {
        current_char = getch();
        editor_buffer_len = strlen(editor_buffer);
        editor_buffer = realloc(editor_buffer,
        (editor_buffer_len + 2) * sizeof(char));

        if (current_char == '\n') {
            UPDATE_CURSORYX
            move(cursoryx.y + 1, 0);
        }
        
        if (current_char == '\x7F') { 
            editor_backspace(editor_buffer, editor_buffer_len);
            clear();
            printw(editor_buffer);
            UPDATE_CURSORYX
            editor_draw_command_line();
            move(cursoryx.y, cursoryx.x);
        }
        if (current_char == ':') {
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
            editor_buffer[editor_buffer_len] = current_char;
            editor_buffer[editor_buffer_len + 1] = '\0';
        }
    }
}
