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

#include <stdio.h>

#include "livsdiary.h"
#include "converters.h"

int main()
{
	convert_to_char_array(3);
	printf("%s\n", converted_int);
	convert_to_char_array(2);
	printf("%s\n", converted_int);
	convert_to_char_array(1);
	printf("%s\n", converted_int);
	convert_to_char_array(0);
	printf("%s\n", converted_int);
	convert_to_char_array(42);
	printf("%s\n", converted_int);
	convert_to_char_array(512);
	printf("%s\n", converted_int);
	convert_to_char_array(1231);
	printf("%s\n", converted_int);

	char test_string[8];
	convert_to_char_array(3);
	strcpy(test_string, converted_int);
	printf("test string = %s\n", test_string);
	convert_to_char_array(0);
	strcpy(test_string, converted_int);
	printf("test string = %s\n", test_string);
	convert_to_char_array(12);
	strcpy(test_string, converted_int);
	printf("test string = %s\n", test_string);
	convert_to_char_array(535);
	strcpy(test_string, converted_int);
	printf("test string = %s\n", test_string);
	convert_to_char_array(1235);
	strcpy(test_string, converted_int);
	printf("test string = %s\n", test_string);
	
	printf("%d\n", convert_to_int("3"));
	printf("%d\n", convert_to_int("2"));
	printf("%d\n", convert_to_int("1"));
	printf("%d\n", convert_to_int("0"));

	return 0;
}
