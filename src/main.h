/*
 * LIVSDiary - (LI)ghtweight (V)irtual (S)imple Diary
 * Copyright (C) 2022 Olivia May - olmay@tuta.io
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

#include "program.h"

#define INPUT_BUFFER 128
#define DIR_BUFFER 48
#define PAGE_COUNT_BUFFER 8

char * get_page_loc();
char * get_page_count_loc();

static char page_count[PAGE_COUNT_BUFFER];

#define HOME_DIR getenv("HOME")
#define PAGE_COUNT_DIR get_page_count_loc()
