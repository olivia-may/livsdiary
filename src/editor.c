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
    printw(":e [number]<enter>                          open page [number]\n");
    printw(":h<enter>               :help<enter>        show this menu\n");
    printw(":n<enter>                                   make new page\n");
    printw(":q<enter>                                   save and quit editor\n");
    printw(":r<enter>                                   remove newest page\n");
    printw("\n");
    printw("Your current page will save when left. Type '\\' to use as an\n");
    printw("escape character. Ex: will let you type ':' without going into\n");
    printw("command mode.\n");
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
    noecho();

    getmaxyx(stdscr, stdscr_maxyx.y, stdscr_maxyx.x);
    move(stdscr_maxyx.y - 1, 0);
    printw("Type ':help<enter>' for help");
    move(0, 0);
}
void editor_exit() {
    echo();
    endwin();
}

void editor_backspace(char *buffer, int buffer_len) {
    if (buffer[0] != '\0') { 
        buffer[buffer_len - 1] = '\0';
        printw("\b \b");
    }
}

// CoordYX so it can pass ':e 2' for example
CoordYX editor_command_mode() {
    int i;
    char *command_str = NULL;
    
    UPDATE_CURSORYX
    move(stdscr_maxyx.y - 1, 0);
    // remove help message from `editor_enter()`
    for (i = 0; i < stdscr_maxyx.x; i++) addch(' ');
    move(stdscr_maxyx.y - 1, 0);
    addch(':');

    command_str = (char *)malloc(2 * sizeof(char));
    i = 0;
    while (true) {
        current_char = getch();
        command_str = (char *)realloc(command_str,( strlen(command_str) + 2)
        * sizeof(char));
        
        if (current_char == '\n') {
            command_str[i] = '\0';
            move(stdscr_maxyx.y - 1, 1);
            for (i = 1; i < stdscr_maxyx.x; i++) addch(' ');
            move(cursoryx.y, cursoryx.x);
            break;
        }
        else if (current_char == '\x7F') {// backspace char "^?"
            editor_backspace(command_str, strlen(command_str));
            i--;
        }
        else {
            command_str[i] = current_char;
            command_str[i + 1] = '\0';
            printw("%c", current_char);
            i++;
        }
    }

    CoordYX retval;
    retval.y = -1; retval.x = 0;
    
#define RETURN free(command_str); return retval;

    if (strncmp(command_str, "q", 2) == 0) {
        retval.y = QUIT; retval.x = 0; RETURN
    }
    if (strncmp(command_str, "h", 2) == 0
    || strncmp(command_str, "help", 5) == 0) {
        retval.y = HELP; retval.x = 0; RETURN
    }
    if (strncmp(command_str, "n", 2) == 0) {
        retval.y = NEW_PAGE; retval.x = 0; RETURN
    }
    if (strncmp(command_str, "r", 2) == 0) {
        retval.y = REMOVE_PAGE; retval.x = 0; RETURN
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
        
        RETURN
    }
    
    RETURN
}

void editor_open_page(char *page_num_str) {
#define CLOSE_PAGE clear(); editor_draw_command_line(); move(0, 0); free(editor_buffer); free(page_loc); free(page_num_str);
#define WRITE_PAGE editor_buffer[editor_buffer_len] = '\0'; page_file = fopen(page_loc, "w"); fprintf(page_file, editor_buffer); fclose(page_file);
    
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

        switch (current_char) {
        case '\x7F': { 
            editor_backspace(editor_buffer, editor_buffer_len);
            clear();
            editor_draw_command_line();
            move(0, 0);
            printw(editor_buffer);
        } break;
        // livsdiary escape char
        case '\\': {
            UPDATE_CURSORYX
            move(cursoryx.y, cursoryx.x - 1);
            current_char = getch();
            editor_buffer[editor_buffer_len] = current_char;
            editor_buffer[editor_buffer_len + 1] = '\0';
            continue;
        } break;
        // ascii escape char
        case '\x1B': {
            current_char = getch();
            if (current_char != '[') continue;
            current_char = getch();
            UPDATE_CURSORYX
            if (current_char == 'D') move(cursoryx.y, cursoryx.x - 1);
            if (current_char == 'C') move(cursoryx.y, cursoryx.x + 1);
            if (current_char == 'A') move(cursoryx.y - 1, cursoryx.x);
            if (current_char == 'B') move(cursoryx.y + 1, cursoryx.x);
        } break;
        case ':': {
            CoordYX command_retval = editor_command_mode();
            switch (command_retval.y) {
                case QUIT: {
                    WRITE_PAGE
                    CLOSE_PAGE
                    editor_exit();
                    exit(0);
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
                    page_num_str = // gets free'd by `CLOSE_PAGE`
                    convert_to_char_array(get_page_count());
                    // recursion B)
                    editor_open_page(page_num_str);
                } break;
                case REMOVE_PAGE: {
                    WRITE_PAGE
                    remove_newest_page();
                    CLOSE_PAGE
                    page_num_str = 
                    convert_to_char_array(get_page_count());
                    editor_open_page(page_num_str);
                } break;
                case OPEN: {
                    WRITE_PAGE
                    CLOSE_PAGE
                    page_num_str = 
                    convert_to_char_array(command_retval.x);
                    editor_open_page(page_num_str);
                } break;
            }
        } break;
        default: {
            editor_buffer[editor_buffer_len] = current_char;
            editor_buffer[editor_buffer_len + 1] = '\0';
            printw("%c", current_char);
        } break;
        }
    }
}
