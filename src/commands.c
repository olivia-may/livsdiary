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

#include <stdlib.h>
#include <string.h>

#include "commands.h"
#include "filesystem.h"
#include "converters.h"

char *get_page_not_found_str(char *arg) {
    char *str = NULL;
    
    str = malloc(64 * sizeof(char));
    strcpy(str, "error: found no page with number '");
    strcat(str, arg);
    strcat(str, "'");
    
    return str;
}

char *get_invalid_page_str(char *arg) {
	char *str = NULL;

    str = malloc(64 * sizeof(char));
    strcpy(str, "error: invalid page number: '");
    strcat(str, arg);
    strcat(str, "', newest page number is '");
    strcat(str, convert_to_char_array(get_page_count()));
    strcat(str, "'");

    return str;
}

char *get_invalid_arg_str(char *arg, int mode) {
   	char *str = NULL;

    str = malloc(64 * sizeof(char));
    strcpy(str, "error: invalid argument '");
    strcat(str, arg);
    strcat(str, "', try '");
    if (mode == COMMAND_LINE) strcat(str, "--help");
    else if (mode == EDITOR) strcat(str, ":help");
    strcat(str, "'");

    return str;
}

bool check_input_is_int(char *input) {
	if (input[0] == '\0') return false;
	for (int i = 0; i < (int)strlen(input); i++) {				
		if (input[i] == '0' ||
		input[i] == '1' ||
		input[i] == '2' ||
		input[i] == '3' ||
		input[i] == '4' ||
		input[i] == '5' ||
		input[i] == '6' ||
		input[i] == '7' ||
		input[i] == '8' ||
		input[i] == '9') continue;
		else return false;
	}

	return true;
}

int is_page_num_found(char *page_num_str) {
    int page_num_str_int;
    unsigned int newest_page_num = get_page_count();
	    
    if (check_input_is_int(page_num_str) == true) {
        page_num_str_int = convert_to_int(page_num_str);
		if (page_num_str_int <= (int)newest_page_num
		&& page_num_str_int >= 0) return PAGE_FOUND;
		else return NO_PAGE_FOUND;
	}
	
    return INVALID_INPUT;
}

void convert_to_equals_sign_arg(char *arg, const int arg_len_at_equals_sign) {
    int i;

	for (i = arg_len_at_equals_sign;
    i < (int)strlen(arg); i++) 
    arg[i - arg_len_at_equals_sign] = arg[i];
	arg[i - arg_len_at_equals_sign] = '\0';
}
