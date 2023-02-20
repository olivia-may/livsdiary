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

#define PROGRAM_DIR "/.livsdiary/"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define DIR_BUFFER 48

static char * HOME_DIR = getenv("HOME");
static char * PAGE_COUNT_DIR = NULL;
static char * CURRENT_PAGE_DIR = NULL;
static char * DUMMY_FILE_DIR = NULL;
static char * PAGE_TIMES_DIR = NULL;

#include "converters.h"
#include "time.h"

char * init_dir(char * dir)
{
	dir = (char *)malloc((strlen(HOME_DIR) + DIR_BUFFER) * sizeof(dir));
	strcpy(dir, HOME_DIR);
	strcat(dir, PROGRAM_DIR);

	return dir;
}

void init()
{
	PAGE_COUNT_DIR = init_dir(PAGE_COUNT_DIR); strcat(PAGE_COUNT_DIR, "info/page_counter");
	CURRENT_PAGE_DIR = init_dir(CURRENT_PAGE_DIR); strcat(CURRENT_PAGE_DIR, "pages/");
	DUMMY_FILE_DIR = init_dir(DUMMY_FILE_DIR); strcat(DUMMY_FILE_DIR, "info/dummy");
	PAGE_TIMES_DIR = init_dir(PAGE_TIMES_DIR); strcat(PAGE_TIMES_DIR, "info/times");

	// check if ~/.livsdiary/info/dummy does not exist
	if (access(DUMMY_FILE_DIR, F_OK) != 0)
	{
		// make needed dirs
		char * working_dir = getenv("HOME");
		strcat(working_dir, "/.livsdiary");
		mkdir(working_dir, 0777);
		strcat(working_dir, "/pages");
		mkdir(CURRENT_PAGE_DIR, 0777);
		working_dir[strlen(working_dir) - 5] = '\0';
		strcat(working_dir, "info");
		mkdir(working_dir, 0777);

		// make needed files
		FILE * working_file = fopen(PAGE_COUNT_DIR, "w");
		fprintf(working_file, "0\0");
		fclose(working_file);
	
		working_file = fopen(PAGE_TIMES_DIR, "w");
		fprintf(working_file, "Table of Contents\n");
		fclose(working_file);

		// make dummy file last
		working_file = fopen(DUMMY_FILE_DIR, "w");
		fclose(working_file);

		// make toc page
		strcat(CURRENT_PAGE_DIR, "0");
		working_file = fopen(CURRENT_PAGE_DIR, "w");
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
		printf("i = %d\n", i);
		printf("ch = %d\n", ch);
		if (ch < 0) { break; }
		//printf("i = %d\n", i);
		file_contents[i] = ch;
		i++;
		file_contents = (char *)realloc(file_contents, (i + 2) * sizeof(file_contents));
	}
	file_contents[i] = '\0';
	fclose(file);

	return file_contents;
}

// this feels kinda dumb but oh well
void increment_page_count()
{
	FILE * page_count_file = fopen(PAGE_COUNT_DIR, "r");
	
	char * temp = convert_to_char_array(convert_to_int(copy_file_to_memory(PAGE_COUNT_DIR)) + 1);
	fclose(page_count_file);
	page_count_file = fopen(PAGE_COUNT_DIR, "w");
	fprintf(page_count_file, temp);
	fprintf(page_count_file, "\0");
	free(temp);
	fclose(page_count_file);
}

void make_new_page()
{
	increment_page_count();
	
	FILE * working_file = fopen(PAGE_TIMES_DIR, "a");
	fprintf(working_file, get_current_time());
	fclose(working_file);
	
	char * latest_page_num = copy_file_to_memory(PAGE_COUNT_DIR);
	printf("latest_page_num = %s\n", latest_page_num);
	strcat(CURRENT_PAGE_DIR, latest_page_num);
	FILE * current_page_file = fopen(CURRENT_PAGE_DIR, "w");
	CURRENT_PAGE_DIR[strlen(CURRENT_PAGE_DIR) - strlen(latest_page_num)] = '\0';
	fclose(current_page_file);
}

void decrement_page_count()
{
	FILE * page_count_file = fopen(PAGE_COUNT_DIR, "r");
	
	char * temp = convert_to_char_array(convert_to_int(copy_file_to_memory(PAGE_COUNT_DIR)) - 1);
	fclose(page_count_file);
	page_count_file = fopen(PAGE_COUNT_DIR, "w");
	fprintf(page_count_file, temp);
	fprintf(page_count_file, "\0");
	free(temp);
	fclose(page_count_file);
}

void remove_most_recent_page()
{	
	char * latest_page_num = copy_file_to_memory(PAGE_COUNT_DIR);
	
	decrement_page_count();
	
	strcat(CURRENT_PAGE_DIR, latest_page_num);
	remove(CURRENT_PAGE_DIR); // remove file
	CURRENT_PAGE_DIR[strlen(CURRENT_PAGE_DIR) - strlen(latest_page_num)] = '\0';
	
	// remove 1 line from the 'times' file
	char * page_times_list = copy_file_to_memory(PAGE_TIMES_DIR);
	page_times_list[strlen(page_times_list) - 25] = '\0';
	FILE * page_times_file = fopen(PAGE_TIMES_DIR, "w");
	fprintf(page_times_file, page_times_list);
	fclose(page_times_file);
}
