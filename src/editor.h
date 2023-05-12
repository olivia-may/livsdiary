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

#ifndef EDITOR_H
#define EDITOR_H

typedef struct {
    int y;
    int x;
} CoordYX;

enum {
    QUIT = 0,
    WRITE,
    WRITE_QUIT,
    HELP,
    NEW_PAGE,
    REMOVE_PAGE,
    OPEN
};

void editor_enter();
void editor_exit();
void editor_open_page(char *page_num_str);

#endif
