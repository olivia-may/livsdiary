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

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

extern char *diary_dir;
extern char *page_count_loc;

char *loc_malloc();
void initialize_diary();
void initialize_locs();
char *get_page_loc(char *page_num_str);
char *get_file_contents(char *loc);
// Use first char as the counter
void set_page_count(unsigned int count);
unsigned int get_page_count();
void free_locs();

void make_new_page();
void remove_newest_page();

#endif
