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
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include "main.h"

int convert_to_int(char * str);
char * convert_to_char_array(int number);
char * get_current_time();

char * init_dir(char * dir)
{
	dir = (char *)malloc((strlen(HOME_DIR) + DIR_BUFFER) * sizeof(dir));
	strcpy(dir, HOME_DIR);
	strcat(dir, PROGRAM_DIR);

	return dir;
}

void init()
{
	PAGE_COUNT_DIR = init_dir(PAGE_COUNT_DIR); strcat(PAGE_COUNT_DIR, "page_counter");
	CURRENT_PAGE_DIR = init_dir(CURRENT_PAGE_DIR);

	// check if PAGE_COUNT_DIR does not exist
	if (access(PAGE_COUNT_DIR, F_OK) != 0)
	{
		// make needed dirs
		mkdir(CURRENT_PAGE_DIR, 0777);
		
		// make page counter
		FILE * working_file = fopen(PAGE_COUNT_DIR, "w");
		fprintf(working_file, "0");
		fclose(working_file);

		// make toc page
		strcat(CURRENT_PAGE_DIR, "0");
		working_file = fopen(CURRENT_PAGE_DIR, "w");
		fprintf(working_file, "** Table of Contents **\n");
		fprintf(working_file, "This page cannot be removed.\n");
		fprintf(working_file, "Feel free remove this message and\n");
		fprintf(working_file, "write anything you want here!\n");
		fprintf(working_file, "Type and enter ':n' to make a new diary entry.\n");
		fclose(working_file);
		CURRENT_PAGE_DIR[strlen(CURRENT_PAGE_DIR) - 1] = '\0';
	}
}

char * copy_file_to_memory(char * dir)
{
	FILE * file = fopen(dir, "r");
	char * file_contents = NULL;
	// 2 because null char
	file_contents = (char *)malloc(2 * sizeof(file_contents));
	int i = 0;
	int ch;
	while (true)
	{
		ch = fgetc(file);
		if (ch < 0) { break; }
		file_contents[i] = ch;
		i++;
		file_contents = (char *)realloc(file_contents, (i + 2) * sizeof(file_contents));
	}
	file_contents[i] = '\0';
	fclose(file);

	return file_contents;
}

void make_new_page()
{
	FILE * page_count_file = fopen(PAGE_COUNT_DIR, "r");	
	char * temp = convert_to_char_array(convert_to_int(copy_file_to_memory(PAGE_COUNT_DIR)) + 1);
	fclose(page_count_file);
	page_count_file = fopen(PAGE_COUNT_DIR, "w");
	fprintf(page_count_file, temp);
	fprintf(page_count_file, "\0");
	free(temp);
	fclose(page_count_file);
	
	char * latest_page_num = copy_file_to_memory(PAGE_COUNT_DIR);
	strcat(CURRENT_PAGE_DIR, latest_page_num);
	FILE * current_page_file = fopen(CURRENT_PAGE_DIR, "w");
	fprintf(current_page_file, "** Page %s **\n", latest_page_num);
	fprintf(current_page_file, "%s\n", get_current_time());
	CURRENT_PAGE_DIR[strlen(CURRENT_PAGE_DIR) - strlen(latest_page_num)] = '\0';
	fclose(current_page_file);
}

void remove_most_recent_page()
{	
	char * most_recent_page_num = copy_file_to_memory(PAGE_COUNT_DIR);
	strcat(CURRENT_PAGE_DIR, most_recent_page_num);
	remove(CURRENT_PAGE_DIR); // remove file
	CURRENT_PAGE_DIR[strlen(CURRENT_PAGE_DIR) - strlen(most_recent_page_num)] = '\0';
	
	FILE * page_count_file = fopen(PAGE_COUNT_DIR, "r");	
	char * temp = convert_to_char_array(convert_to_int(copy_file_to_memory(PAGE_COUNT_DIR)) - 1);
	fclose(page_count_file);
	page_count_file = fopen(PAGE_COUNT_DIR, "w");
	fprintf(page_count_file, temp);
	fprintf(page_count_file, "\0");
	free(temp);
	fclose(page_count_file);
}
