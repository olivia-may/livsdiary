/* (C) 2022 Olivia May GPLv3+ */

#define PROGRAM_VERSION "v1.1.1"

#define INPUT_BUFFER 128
#define PAGE_COUNT_BUFFER 8
#define TIMES_STORAGE_BUFFER 64
#define FILE_BUFFER 4096
// linux max file name size is 255 chars
#define DIR_BUFFER 320

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char PAGE_COUNT_DIR[DIR_BUFFER];
static char CURRENT_PAGE_DIR[DIR_BUFFER];
static char DUMMY_FILE_DIR[DIR_BUFFER];
static char PAGE_TIMES_DIR[DIR_BUFFER];
static FILE * working_file;
static char file_contents[FILE_BUFFER];
static char page_count[PAGE_COUNT_BUFFER];
static char ch;

// set up the dirs in memory instead of changing the length of working_dir all the time
void init()
{
	strcpy(PAGE_COUNT_DIR, getenv("HOME"));
	strcat(PAGE_COUNT_DIR, "/.livsdiary/info/page_counter");

	strcpy(CURRENT_PAGE_DIR, getenv("HOME"));
	strcat(CURRENT_PAGE_DIR, "/.livsdiary/pages/");

	strcpy(DUMMY_FILE_DIR, getenv("HOME"));
	strcat(DUMMY_FILE_DIR, "/.livsdiary/info/dummy");
		
	strcpy(PAGE_TIMES_DIR, getenv("HOME"));
	strcat(PAGE_TIMES_DIR, "/.livsdiary/info/times");
}
