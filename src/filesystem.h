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

#include <sys/stat.h>
#include <unistd.h>

// to `file_contents`
void copy_file_to_memory(char * dir)
{
	working_file = fopen(dir, "r");
	int i = 0;
	while (true)
	{
		ch = fgetc(working_file);
		if (ch < 0) { break; }
		file_contents[i] = ch;
		i++;
	}
	file_contents[i] = '\0';
	fclose(working_file);
}

// this feels kinda dumb but oh well
void increment_page_count()
{
	copy_file_to_memory(PAGE_COUNT_DIR);
	working_file = fopen(PAGE_COUNT_DIR, "w");
	convert_to_char_array(convert_to_int(file_contents) + 1);
	fprintf
	(
		working_file,
		converted_int
	);
	fclose(working_file);
}

void make_new_page()
{
	increment_page_count();
	
	working_file = fopen(PAGE_TIMES_DIR, "a");
	fprintf(working_file, get_current_time());
	fclose(working_file);
	
	copy_file_to_memory(PAGE_COUNT_DIR);
	strcat(CURRENT_PAGE_DIR, file_contents);
	working_file = fopen(CURRENT_PAGE_DIR, "w");
	CURRENT_PAGE_DIR[strlen(CURRENT_PAGE_DIR) - strlen(file_contents)] = '\0';
	fclose(working_file);
}



void decrement_page_count()
{
	copy_file_to_memory(PAGE_COUNT_DIR);
	working_file = fopen(PAGE_COUNT_DIR, "w");
	convert_to_char_array(convert_to_int(file_contents) - 1);
	fprintf
	(
		working_file, 
		converted_int
	);
	fclose(working_file);
}

void remove_most_recent_page()
{	
	copy_file_to_memory(PAGE_COUNT_DIR);
	
	decrement_page_count();
	
	strcat(CURRENT_PAGE_DIR, file_contents);
	remove(CURRENT_PAGE_DIR); // remove file
	CURRENT_PAGE_DIR[strlen(CURRENT_PAGE_DIR)- strlen(file_contents)] = '\0';
	
	// remove 1 line from the 'times' file
	copy_file_to_memory(PAGE_TIMES_DIR);
	file_contents[strlen(file_contents) - 25] = '\0';
	working_file = fopen(PAGE_TIMES_DIR, "w");
	fprintf(working_file, file_contents);
	fclose(working_file);
}
