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

#include "config.h"
#include "editor.h"
#include "filesystem.h"

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

void insert_char(char *buffer, int buffer_len, char ch, int index) {
    int i;
    // move everything right to make space for inserting the char
    for (i = buffer_len + 1; i >= index; i--) {
        buffer[i] = buffer[i - 1];
    }
    buffer[index] = ch;
}

void insert_backspace(char *buffer, int buffer_len, int index) {
    int i;
    // move everything right into the index, we dont care about it!
    if (buffer_len < 1) { 
        for (i = index - 1; i < buffer_len + 1; i++) {
            buffer[i] = buffer[i + 1];
        }
    }
}

char *get_command_str() {
    int i;
    char *command_str = NULL;

    command_str = (char *)malloc(2 * sizeof(char));
    i = 0;
    while (true) {
        current_char = getch();
        command_str = (char *)realloc(command_str,( strlen(command_str) + 2)
        * sizeof(char));
        
        switch (current_char) {
        case '\n': {
            command_str[i] = '\0';
            move(stdscr_maxyx.y - 1, 1);
            for (i = 1; i < stdscr_maxyx.x; i++) addch(' ');
            move(cursoryx.y, cursoryx.x);
            return command_str;
        }
        case '\x7F': { // backspace char "^?"
            insert_backspace(command_str, strlen(command_str), strlen(command_str) - 1);
            for (i = 1; i < stdscr_maxyx.x; i++) addch(' ');
            move(stdscr_maxyx.y - 1, 1);
            printw(command_str);
            
        } break;
        case '\x1B': { // if 'ESC' pressed leave command mode
            free(command_str); command_str = NULL; return command_str;
        }
        default: {
            command_str[i] = current_char;
            command_str[i + 1] = '\0';
            printw("%c", current_char);
            i++;
        } break;
    }
    }
}

// CoordYX so it can pass ':e 2' for example
CoordYX editor_command_mode() {
#define RETURN free(command_str); return retval;
    
    int i;
    char *command_str = NULL;
    CoordYX retval;
    
    UPDATE_CURSORYX
    move(stdscr_maxyx.y - 1, 0);
    // remove help message from `editor_enter()`
    for (i = 0; i < stdscr_maxyx.x; i++) addch(' ');
    move(stdscr_maxyx.y - 1, 0);
    addch(':');

    retval.y = DO_NOTHING; retval.x = 0; 

    command_str = get_command_str();
    if (command_str == NULL) return retval;
    
    switch (command_str[0]) {
    case 'q': {
        retval.y = QUIT; RETURN
    } break;
    case 'h': {
        retval.y = HELP; RETURN
    } break;
    case 'n': {
        retval.y = NEW_PAGE; RETURN
    } break;
    case 'r': {
        retval.y = REMOVE_PAGE; RETURN
    } break;
    case 'e': {
        int first_arg_len = 0;

        retval.y = OPEN;

        for (i = 0; i < (int)strlen(command_str); i++) {
            if (check_input_is_unsigned_int(&command_str[i])) {
                first_arg_len = i - 1; break;
            }
        }
        convert_to_second_arg(command_str, first_arg_len);

        if (check_input_is_unsigned_int(command_str)) {
            int command_int = convert_to_unsigned_int(command_str);		
            if (command_int <= (int)get_page_count()
            && command_int >= 0) retval.x = command_int;
            else retval.x = -1;
        }
        else retval.x = -1; // re-open current page
        
        RETURN
    } break;
    }
    
    RETURN
}

// so the user can insert and delete chars anywhere the cursor is
int get_buffer_index_from_cursoryx() {
    int buffer_index;
    CoordYX buffer_index_position;

    buffer_index = 0;
    buffer_index_position.y = 0;
    buffer_index_position.x = 0;
    while (true) {
        if (buffer_index_position.x == cursoryx.x
        && buffer_index_position.y == cursoryx.y) break;

        if (editor_buffer[buffer_index] == '\0'
        || editor_buffer_len == buffer_index + 1) {
            buffer_index++; break;
        }

        if (editor_buffer[buffer_index] == '\n'
        || buffer_index_position.x == stdscr_maxyx.x - 1) {
            buffer_index_position.x = 0;
            buffer_index_position.y++;
            buffer_index++;
            continue;
        }

        buffer_index++;
        buffer_index_position.x++;
    }

    return buffer_index;
}

void editor_open_page(char *page_num_str) {
#define CLOSE_PAGE clear(); editor_draw_command_line(); move(0, 0); free(editor_buffer); free(page_loc); free(page_num_str);
#define WRITE_PAGE editor_buffer[editor_buffer_len] = '\0'; page_file = fopen(page_loc, "w"); fprintf(page_file, "%s", editor_buffer); fclose(page_file);
#define CLEAR_SCREEN  clear(); editor_draw_command_line(); move(0, 0);
    
    FILE *page_file = NULL;
    char *page_loc = NULL;
    int buffer_index;

    page_loc = get_page_loc(page_num_str);
    editor_buffer = get_file_contents(page_loc);
    printw("%s", editor_buffer);

    while (true) {
        current_char = getch();
        editor_buffer_len = strlen(editor_buffer);
        editor_buffer = realloc(editor_buffer,
        (editor_buffer_len + 3) * sizeof(char));

        switch (current_char) {
        case '\x7F': { // backspace
            UPDATE_CURSORYX
            buffer_index = get_buffer_index_from_cursoryx();
            
            insert_backspace(editor_buffer, editor_buffer_len, buffer_index);
            CLEAR_SCREEN
            printw("%s", editor_buffer);
            move(cursoryx.y, cursoryx.x - 1);
        } break;
        case '\\': { // livsdiary escape char
            UPDATE_CURSORYX
            buffer_index = get_buffer_index_from_cursoryx();

            insert_char(editor_buffer, editor_buffer_len,
            current_char, buffer_index);
            CLEAR_SCREEN
            printw("%s", editor_buffer);
            move(cursoryx.y, cursoryx.x);

            current_char = getch();
            insert_backspace(editor_buffer, editor_buffer_len,
            buffer_index + 1);
            insert_char(editor_buffer, editor_buffer_len,
            current_char, buffer_index);
            CLEAR_SCREEN
            printw("%s", editor_buffer);
            move(cursoryx.y, cursoryx.x + 1);
            continue;
        } break;
        case '\x1B': { // ascii escape char
            current_char = getch();
            if (current_char != '[') continue;
            current_char = getch();
            UPDATE_CURSORYX
            if (current_char == 'D') move(cursoryx.y, cursoryx.x - 1);
            if (current_char == 'C') move(cursoryx.y, cursoryx.x + 1);
            if (current_char == 'A') move(cursoryx.y - 1, cursoryx.x);
            if (current_char == 'B') move(cursoryx.y + 1, cursoryx.x);
        } break;
        case '\n': {
            UPDATE_CURSORYX
            buffer_index = get_buffer_index_from_cursoryx();
            
            insert_char(editor_buffer, editor_buffer_len, 
            current_char, buffer_index);
            CLEAR_SCREEN
            printw("%s", editor_buffer);
            move(cursoryx.y + 1, 0);
        } break;
        case ':': {
            CoordYX command_retval = editor_command_mode();
            switch (command_retval.y) {
            case DO_NOTHING: {
                move(stdscr_maxyx.y - 1, 0);
                for (int i = 0; i < stdscr_maxyx.x; i++) addch(' ');
                editor_draw_command_line();
                move(0, 0);
                printw("%s", editor_buffer);
            } break;
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
                printw("%s", editor_buffer);
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
                editor_draw_command_line();
                move(0, 0);
                free(editor_buffer);
                free(page_loc);
                CLEAR_SCREEN
                if (command_retval.x != -1) {
                free(page_num_str);
                page_num_str =
                convert_to_char_array(command_retval.x);
                }
                editor_open_page(page_num_str);
            } break;
            }
        } break;
        default: {
            UPDATE_CURSORYX
            buffer_index = get_buffer_index_from_cursoryx();

            insert_char(editor_buffer, editor_buffer_len, 
            current_char, buffer_index);
            CLEAR_SCREEN
            printw("%s", editor_buffer);
            move(cursoryx.y, cursoryx.x + 1);
        } break;
        }
    }
}
