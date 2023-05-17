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

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "converters.h"
#include "filesystem.h"
#include "time.h"

unsigned int page_count = 0;

char *loc_malloc() {
    return (char *)malloc(
        // `48` is a buffer
        (strlen(getenv("HOME")) + 48) * sizeof(char)
    );
}

void initialize_diary() {
    char *working_loc = NULL;
    FILE *page_count_file = NULL;
    FILE *table_of_contents_file = NULL;

    working_loc = loc_malloc();
    strcat(working_loc, getenv("HOME"));
    strcat(working_loc, "/.local/");
    mkdir(working_loc, 0777); // permissions are weird
    strcat(working_loc, "share/");
    mkdir(working_loc, 0777);
    strcat(working_loc, "livsdiary/"); 
    mkdir(working_loc, 0777);
    
    strcat(working_loc, "page_count.dat");
    page_count_file = fopen(working_loc, "w");
    fwrite(&page_count, sizeof(unsigned int), 1, page_count_file);
    // 14 is length of `"page_count.dat"`
    working_loc[strlen(working_loc) - 14] = '\0';

    strcat(working_loc, "0.txt");
    table_of_contents_file = fopen(working_loc, "w");
    fprintf(table_of_contents_file, "** Table of Contents **\n");
    fprintf(table_of_contents_file, "This page cannot be removed.\n");
    fprintf(table_of_contents_file, "Feel free remove this message and\n");
    fprintf(table_of_contents_file, "write anything you want here!\n");
    fprintf(table_of_contents_file, "Type and enter ':n' to make a new diary entry.\n");
    
    free(working_loc);
    fclose(page_count_file);
    fclose(table_of_contents_file);
}

char *get_diary_dir() {
    char *dir = NULL;

    dir = loc_malloc();
	strcpy(dir, getenv("HOME"));
	strcat(dir, "/.local/share/livsdiary/");

    return dir;
}

char *get_page_count_loc() {
	char *loc = NULL; 

    loc = loc_malloc();
    strcpy(loc, get_diary_dir());
    strcat(loc, "page_count.dat\0");

	return loc;
}

char *get_page_loc(char *page_num_str) {
    char *loc = NULL;

    loc = loc_malloc();
    strcpy(loc, get_diary_dir());
    strcat(loc, page_num_str);
    strcat(loc, ".txt");

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

void set_page_count(unsigned int count) {
    FILE *file = fopen(get_page_count_loc(), "w");
    fwrite(&count, sizeof(unsigned int), 1, file);
    fclose(file);
}
unsigned int get_page_count() {
    FILE *file = fopen(get_page_count_loc(), "r");
	unsigned int count;
    fread(&count, sizeof(unsigned int), 1, file);
    fclose(file);

    return count;
}

void make_new_page() {
    FILE *new_page_file = NULL;
    
    page_count = get_page_count();
    page_count = page_count + 1;
    set_page_count(page_count);

	new_page_file = fopen(get_page_loc(convert_to_char_array(page_count)), "w");
	fprintf(new_page_file, "** Page %d **\n", page_count);
	fprintf(new_page_file, "%s\n", get_current_time());

    free(get_page_loc(convert_to_char_array(page_count)));
    fclose(new_page_file);
}

void remove_newest_page() {
    page_count = get_page_count();
	remove(get_page_loc(convert_to_int(page_count))); // remove file
    set_page_count(page_count - 1);

    free(get_page_loc(convert_to_char_array(page_count)));
}
