/* 
 * LIVSDiary
 * (C) 2022 Olivia May - olmay@tuta.io GPLv3+
 *
 * (LI)ghtweight (V)irtual (S)imple Diary
 *
 * A program that should make a directory in the user's home folder. 
 * And be able to store a diary on the user's hard drive. Maybe also
 * in memory too when it runs. It will be a command line program.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#define PROGRAM_VERSION "v1.1.2"
#define PROGRAM_DIR "/.livsdiary/"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define INPUT_BUFFER 128
#define PAGE_COUNT_BUFFER 8
#define TIMES_STORAGE_BUFFER 64
#define FILE_BUFFER 4096
#define DIR_BUFFER 48

static char * HOME_DIR = getenv("HOME");
static char * PAGE_COUNT_DIR = NULL;
static char * CURRENT_PAGE_DIR = NULL;
static char * DUMMY_FILE_DIR = NULL;
static char * PAGE_TIMES_DIR = NULL;
static FILE * working_file;
static char file_contents[FILE_BUFFER];
static char page_count[PAGE_COUNT_BUFFER];
static char ch;

#include "converters.h"
#include "time.h"
#include "filesystem.h"
#include "page.hpp"
#include "command_line.hpp"

char * init_dir(char * dir)
{
	dir = (char *)malloc((strlen(HOME_DIR) + DIR_BUFFER) * sizeof(dir));
	strcpy(dir, HOME_DIR);
	strcat(dir, PROGRAM_DIR);

	return dir;
}

int main(int argc, char * argv[])
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
		working_file = fopen(PAGE_COUNT_DIR, "w");
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

	command_logic(argc, argv);
	
	return 0;
}
