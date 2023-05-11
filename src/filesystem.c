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

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "converters.h"
#include "filesystem.h"
#include "time.h"

char *loc_malloc() {
    return (char *)malloc(
        (strlen(getenv("HOME")) + DIR_BUFFER) * sizeof(char)
    );
}

void initialize_diary() {
    char *working_loc = NULL; working_loc = loc_malloc();
    FILE *page_counter_file = NULL;
    FILE *table_of_contents_file = NULL;

    strcat(working_loc, getenv("HOME"));
    strcat(working_loc, "/.local/");
    mkdir(working_loc, 0777); // permissions are weird
    strcat(working_loc, "share/");
    mkdir(working_loc, 0777);
    strcat(working_loc, "livsdiary/"); 
    mkdir(working_loc, 0777);
    
    strcat(working_loc, "page_counter");
    page_counter_file = fopen(working_loc, "w");
    fputc((char)0, page_counter_file);
    // 12 is length of `"page_counter"`
    working_loc[strlen(working_loc) - 12] = '\0';

    strcat(working_loc, "0");
    table_of_contents_file = fopen(working_loc, "w");
    fprintf(table_of_contents_file, "** Table of Contents **\n");
    fprintf(table_of_contents_file, "This page cannot be removed.\n");
    fprintf(table_of_contents_file, "Feel free remove this message and\n");
    fprintf(table_of_contents_file, "write anything you want here!\n");
    fprintf(table_of_contents_file, "Type and enter ':n' to make a new diary entry.\n");
    
    free(working_loc);
    fclose(page_counter_file);
    fclose(table_of_contents_file);
}

char *get_diary_dir() {
    char *dir = NULL; dir = loc_malloc();
	strcpy(dir, getenv("HOME"));
	strcat(dir, "/.local/share/livsdiary/");

    return dir;
}

char *get_page_counter_loc() {
	char *loc = NULL; loc = loc_malloc();
    strcpy(loc, get_diary_dir());
    strcat(loc, "page_counter\0");

	return loc;
}

char *get_file_contents(char *loc) {
	FILE *file = fopen(loc, "r");
	char *file_contents = NULL;
	// 2 because null char
	file_contents = (char *)malloc(2 * sizeof(char));
	int i = 0;
	int ch;
	while (true) {
		ch = fgetc(file);
		if (ch < 0) break;
		file_contents[i] = ch;
		i++;
		file_contents = 
        (char *)realloc(file_contents, (i + 2) * sizeof(char));
	}
	file_contents[i] = '\0';
	fclose(file);

	return file_contents;
}

void set_page_count(char count) {
    FILE *file = fopen(get_page_counter_loc(), "w");
    fputc(count, file);
    fclose(file);
}
char get_page_count() {
    FILE *file = fopen(get_page_counter_loc(), "r");
	char count;
    count = fgetc(file);
    fclose(file);

    return count;
}

void make_new_page() {
    char *working_loc = NULL; working_loc = loc_malloc();
    FILE *new_page_file = NULL;
    char page_count = get_page_count();

    set_page_count(page_count + 1);
	
    strcpy(working_loc, get_diary_dir());
    // Use '13' string instead of unicode 13 char
	strcat(working_loc, convert_to_char_array((int)get_page_count()));
	new_page_file = fopen(working_loc, "w");
	fprintf(new_page_file, "** Page %d **\n", get_page_count());
	fprintf(new_page_file, "%s\n", get_current_time());

    free(working_loc);
    fclose(new_page_file);
}

void remove_newest_page() {
    char *working_loc = NULL; working_loc = loc_malloc();

	strcpy(working_loc, get_diary_dir());
	strcat(working_loc, convert_to_char_array((int)get_page_count()));
	remove(working_loc); // remove file
	
    set_page_count(get_page_count() - 1);

    free(working_loc);
}
