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

#include "editor.h"
#include "filesystem.h"

void editor_draw_command_line() {
    CoordYX stdscr_max;

    getmaxyx(stdscr, stdscr_max.y, stdscr_max.x);
    move(stdscr_max.y - 1, 0);
    addch(':');
    move(0, 0);
}

void editor_enter() {
    initscr();
    cbreak();
    echo();

    editor_draw_command_line();
}
void editor_exit() {
    endwin();
}
int editor_command_mode() {
    CoordYX cursor_coord;
    CoordYX stdscr_max;
    char ch;
    int i;
    char command_str[8];
    
    getyx(stdscr, cursor_coord.y, cursor_coord.x);
    getmaxyx(stdscr, stdscr_max.y, stdscr_max.x);
    move(stdscr_max.y - 1, 1);

    i = 0;
    while (true) {
        ch = getch();
        if (ch == '\n') {
            command_str[i] = '\0';
            move(stdscr_max.y - 1, 1);
            for (i = 1; i < stdscr_max.x; i++) addch(' ');
            move(cursor_coord.y, cursor_coord.x);
            break;
        }
        command_str[i] = ch;

        if (i != 7) i++;
    }
    
    if (command_str[0] == 'q') return QUIT;
    if (command_str[0] == 'w') return WRITE;
    else return -1;
}

void editor_open_page(char *page_num_str) {
    char *page_loc = NULL; page_loc = loc_malloc();
    char *editor_buffer = NULL;
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
            move(0, 0);
            clear();
            editor_draw_command_line();
            if (editor_buffer[0] != '\0') { 
                editor_buffer[editor_buffer_len - 1] = '\0';
                printw(editor_buffer);
            }
        }
        else if (ch == ':') {
            printw("\b \b"); // dont show ':'
            switch (editor_command_mode()) {
                case QUIT: { editor_exit(); return; }
                case WRITE: {
                    editor_buffer[editor_buffer_len] = '\0';
                    
                    FILE *page_file = fopen(page_loc, "w");
                    fprintf(page_file, editor_buffer);
                } break;
            }
        }
        else {
            editor_buffer[editor_buffer_len] = ch;
            editor_buffer[editor_buffer_len + 1] = '\0';
        }
    }
}
