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

#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "converters.h"

// i tried, and it feels weird doing this, but i cant find anything for this, so i dont know what else to do
char *convert_to_char_array(int number) {
	char *converted_int = NULL;
	converted_int = (char *)malloc(2 * sizeof(int));

	if (number == 0) {
		converted_int[0] = '0';
		converted_int[1] = '\0';
		return converted_int;
	}
	
	int i = 0;
	while (true) {
		if (number == 0) break;
		else i++;

		if (number % 10 == 0) converted_int[i] = '0';
		if (number % 10 == 1) converted_int[i] = '1';
		if (number % 10 == 2) converted_int[i] = '2';
		if (number % 10 == 3) converted_int[i] = '3';
		if (number % 10 == 4) converted_int[i] = '4';
		if (number % 10 == 5) converted_int[i] = '5';
		if (number % 10 == 6) converted_int[i] = '6';
		if (number % 10 == 7) converted_int[i] = '7';
		if (number % 10 == 8) converted_int[i] = '8';
		if (number % 10 == 9) converted_int[i] = '9';
		
		converted_int = (char *)realloc(converted_int, (i + 2) * sizeof(int));
		number = number / 10;
	}
	
	// reverse array
	int halfway_point = i/ 2;
	char ch;
	for (int j = 0; j <= halfway_point; j++) {
		ch = converted_int[j];
		int last = i - j;
		converted_int[j] = converted_int[last];
		converted_int[last] = ch;
	}
	converted_int[i] = '\0';

	return converted_int;
}

// warning: will break for long numbers (int digit_slot overflows), like '12343678912'
int convert_to_int(char *str) {
	int number = 0;
	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		int digit_slot = pow(10, len - i - 1);

		if (str[i] == '0') number = number + 0 * digit_slot;
		if (str[i] == '1') number = number + 1 * digit_slot;
		if (str[i] == '2') number = number + 2 * digit_slot;
		if (str[i] == '3') number = number + 3 * digit_slot;
		if (str[i] == '4') number = number + 4 * digit_slot;
		if (str[i] == '5') number = number + 5 * digit_slot;
		if (str[i] == '6') number = number + 6 * digit_slot;
		if (str[i] == '7') number = number + 7 * digit_slot;
		if (str[i] == '8') number = number + 8 * digit_slot;
		if (str[i] == '9') number = number + 9 * digit_slot;
	}

	return number;
}

bool check_input_is_int(char *input) {
	if (input[0] == '\0') return false;
	for (int i = 0; i < strlen(input); i++) {				
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
