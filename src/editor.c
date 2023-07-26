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
#include "commands.h"
#include "editor.h"
#include "filesystem.h"

char current_char;
int editor_buffer_len;
CoordYX cursoryx;
CoordYX stdscr_maxyx;
char *editor_buffer = NULL;



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
    if (buffer_len >= 1 && index != 0) { 
        for (i = index - 1; i <= buffer_len; i++) {
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
            i--;
            command_str[i] = '\0';
            getyx(stdscr, cursoryx.y, cursoryx.x); 
            move(cursoryx.y, cursoryx.x - 1);
            addch(' ');
            move(cursoryx.y, cursoryx.x - 1);
            
        } break;
        /* FIXME arrow keys exit command mode and write in the diary
        case '\x1B': { // if 'ESC' pressed leave command mode
            free(command_str); command_str = NULL; return command_str;
        } break;
        */
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
    int i;
    char *command_str = NULL;
    CoordYX retval;
    
    getyx(stdscr, cursoryx.y, cursoryx.x);
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
        retval.y = QUIT;
    } break;
    case 'h': {
        retval.y = HELP;
    } break;
    case 'l': {
        retval.y = LICENSE;
    } break;
    case 'n': {
        retval.y = NEW_PAGE;
    } break;
    case 'r': {
        retval.y = REMOVE_PAGE;
    } break;
    case 'e': {
        unsigned int command_int = 0;

        retval.y = OPEN;

        for (i = 0; i < (int)strlen(command_str); i++) {
            if (check_input_is_unsigned_int(&command_str[i])) {
                command_int = convert_to_unsigned_int(&command_str[i]);
                break;
            }
        }

        if (command_int <= get_page_count()) retval.x = command_int;
        else retval.x = -1; // re-open current page
    } break;
    }
    
    free(command_str);
    return retval;
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
        || editor_buffer_len == buffer_index) break;
        
        if (editor_buffer[buffer_index] == '\n'
        || buffer_index_position.x == stdscr_maxyx.x - 1) {
            if (cursoryx.y == buffer_index_position.y
            && cursoryx.x != buffer_index_position.x) break;

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
            getyx(stdscr, cursoryx.y, cursoryx.x);
            buffer_index = get_buffer_index_from_cursoryx();
            insert_backspace(editor_buffer, editor_buffer_len, buffer_index);
            CLEAR_SCREEN
            printw("%s", editor_buffer);

            move(cursoryx.y, cursoryx.x - 1);
        } break;
        case '\\': { // livsdiary escape char
            getyx(stdscr, cursoryx.y, cursoryx.x);
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
            getyx(stdscr, cursoryx.y, cursoryx.x);
            buffer_index = get_buffer_index_from_cursoryx();
            if (current_char == 'D' && cursoryx.x != 0) move(cursoryx.y, cursoryx.x - 1);
            if (current_char == 'C' && !(editor_buffer[buffer_index] == '\n'
            || editor_buffer[buffer_index] == '\0'))
            move(cursoryx.y, cursoryx.x + 1);
            if (current_char == 'A' && cursoryx.y != 0) move(cursoryx.y - 1, cursoryx.x);
            if (current_char == 'B' && editor_buffer[buffer_index] != '\0')
            move(cursoryx.y + 1, cursoryx.x);
        } break;
        case '\n': {
            getyx(stdscr, cursoryx.y, cursoryx.x);
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
                clear();
                printw("** LIVSDiary %s Editor Help **\n", VERSION);
                printw(":e [number]<enter>                          open page [number]\n");
                printw(":h<enter>               :help<enter>        show this menu\n");
                printw(":l<enter>               :license<enter>     view GPLv3+ license info\n");
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

                editor_draw_command_line();
                move(0, 0);
                printw("%s", editor_buffer);
            } break;
            case LICENSE: {
                clear();
                printw("LIVSDiary %s Copyright (C) 2022 Olivia May\n", VERSION);
                printw("This program comes with ABSOLUTELY NO WARRANTY; for details type 'w'\n");
                printw("This is free software, and you are welcome to\n");
                printw("redistribute it under certain conditions; type 'c' for details\n");
                printw("\n");
                printw("Press 'w' to view disclaimer of warranty, 'c' to view redistribution\nconditions, or any other key to go back to editing.\n");

                current_char = getch();
                clear();

                if (current_char == 'w') {
                printw("----------------------------------------------------------------\n");
                printw("  15. Disclaimer of Warranty.\n\n  THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY\nAPPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT\nHOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM \"AS IS\" WITHOUT WARRANTY\nOF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,\nTHE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR\nPURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM\nIS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF\nALL NECESSARY SERVICING, REPAIR OR CORRECTION.\n");
                printw("----------------------------------------------------------------\n");
                printw("\n");
                printw("Press any key to go back to editing.\n");
                getch();
                clear();
                }
                else if (current_char == 'c') {
                printw("----------------------------------------------------------------\n");
                printw("  2. Basic Permissions.\n  All rights granted under this License are granted for the term of\ncopyright on the Program, and are irrevocable provided the stated\nconditions are met.  This License explicitly affirms your unlimited\npermission to run the unmodified Program.  The output from running a\ncovered work is covered by this License only if the output, given its\ncontent, constitutes a covered work.  This License acknowledges your\nrights of fair use or other equivalent, as provided by copyright law.\n\n  You may make, run and propagate covered works that you do not\nconvey, without conditions so long as your license otherwise remains\nin force.  You may convey covered works to others for the sole purpose\nof having them make modifications exclusively for you, or provide you\nwith facilities for running those works, provided that you comply with\nthe terms of this License in conveying all material for which you do\nnot control copyright.  Those thus making or running the covered works\nfor you must do so exclusively on your behalf, under your direction\nand control, on terms that prohibit them from making any copies of\nyour copyrighted material outside their relationship with you.\n\n  Conveying under any other circumstances is permitted solely under\nthe conditions stated below.  Sublicensing is not allowed; section 10\nmakes it unnecessary.\n");

                printw("----------------------------------------------------------------\n");
                printw("\n");
                printw("Press any key to go back to editing.\n");
                getch();
                clear();
                }

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
            getyx(stdscr, cursoryx.y, cursoryx.x);
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
