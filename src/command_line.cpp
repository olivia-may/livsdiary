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

#include "livsdiary.h"
#include "converters.h"
#include "time.h"
#include "filesystem.h"
#include "page.hpp"
#include "command_line.hpp"

int main()
{
	printf("** command_line.cpp **\n");

	check_dirs_and_files();
	
	char * array[2];
	array[0] = "test1";
	array[1] = "-n";
	command_logic(1, array);
	command_logic(2, array);

	invalid("test");
	no_arg();
	version();
	help();
	printf("%b\n", check_input_is_int("test"));
	printf("%b\n", check_input_is_int("1"));
	printf("%b\n", check_input_is_int("123"));
	check_input_is_int("1");

	//edit("1");

	return 0;
}
