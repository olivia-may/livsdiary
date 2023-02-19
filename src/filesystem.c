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

int main()
{
	printf("** filesystem.c **\n");
	
	// `working_dir` should always be '~/.livsdiary'

	init();
	
	printf("%s\n", PAGE_COUNT_DIR);
	printf("%s\n", CURRENT_PAGE_DIR);
	printf("%s\n", DUMMY_FILE_DIR);
	printf("%s\n", PAGE_TIMES_DIR);
	
	check_dirs_and_files();
	copy_file_to_memory(PAGE_COUNT_DIR);
	copy_file_to_memory(PAGE_TIMES_DIR);

	// check page counter file
	printf("increment_page_count\n");
	increment_page_count();
	increment_page_count();
	
	printf("decrement_page_count\n");
	decrement_page_count();	
	decrement_page_count();	

	make_new_page();
	make_new_page();
	make_new_page();
	make_new_page();

	remove_most_recent_page();

	return 0;
}
