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

#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdbool.h>

enum {
    PAGE_FOUND = 0,
    NO_PAGE_FOUND,
    INVALID_INPUT
};

// modes
enum {
    COMMAND_LINE = 0,
    EDITOR
};

char *get_page_not_found_str(char *arg);
char *get_invalid_page_str(char *arg);
char *get_invalid_arg_str(char *arg, int mode);
bool check_input_is_int(char *input);
int is_page_num_found(char *page_num_str);
void convert_to_equals_sign_arg();

#endif
