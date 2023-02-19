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

int main()
{
	printf("** page.cpp **\n");

	check_dirs_and_files();
	
	printf("%s\n", working_dir);
	Page test;
	test.page_num = "1";
	printf("%s\n", test.page_num);
	test.edit();
	printf("%s\n", working_dir);
}
