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

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#include "filesystem.h"

char *diary_dir = NULL;
char *page_count_loc = NULL;
unsigned int page_count = 0;

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

int convert_to_unsigned_int(char *str) {
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

void initialize_locs() {
    diary_dir = loc_malloc();
    strcpy(diary_dir, getenv("HOME"));
    strcat(diary_dir, "/.local/share/livsdiary/");
    page_count_loc = loc_malloc();
    strcpy(page_count_loc, diary_dir);
    strcat(page_count_loc, "page_count.dat\0");
}

char *get_page_loc(char *page_num_str) {
    char *loc = NULL;

    loc = loc_malloc();
    strcpy(loc, diary_dir);
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
    FILE *file = fopen(page_count_loc, "w");
    fwrite(&count, sizeof(unsigned int), 1, file);
    fclose(file);
}
unsigned int get_page_count() {
    FILE *file = fopen(page_count_loc, "r");
    unsigned int count;
    fread(&count, sizeof(unsigned int), 1, file);
    fclose(file);

    return count;
}

char *get_current_time() {
    time_t now = time(0);
    struct tm *lt = localtime(&now);
    char *current_time = asctime(lt);
    current_time[strlen(current_time) - 1] = ' ';
    strcat(current_time, lt->tm_zone);
	
    return current_time;
}

void make_new_page() {
    FILE *new_page_file = NULL;
    char *page_count_str = NULL;
    char *page_loc = NULL;
    
    page_count = get_page_count();
    page_count = page_count + 1;
    set_page_count(page_count);

    page_count_str = convert_to_char_array(page_count);
    page_loc = get_page_loc(page_count_str);
    new_page_file = fopen(page_loc, "w");
    fprintf(new_page_file, "** Page %s **\n", page_count_str);
    fprintf(new_page_file, "%s\n", get_current_time());

    free(page_loc);
    free(page_count_str);
    fclose(new_page_file);
}

void remove_newest_page() {
    char *page_count_str = NULL;
    char *page_loc = NULL;

    page_count = get_page_count();
    page_count_str = convert_to_char_array(page_count);
    page_loc = get_page_loc(page_count_str);
    // remove file
    remove(page_loc);
    set_page_count(page_count - 1);

    free(page_count_str);
    free(page_loc);
}

void free_locs() {
    free(page_count_loc);
    free(diary_dir);
}

