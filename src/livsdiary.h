/* (C) 2022 Olivia May GPLv3+ */

#define PROGRAM_VERSION "v1.0.0"

#define PAGE_BUFFER 4096
#define INPUT_BUFFER 128
#define PAGE_COUNT_BUFFER 8
#define TIMES_STORAGE_BUFFER 64
#define FILE_BUFFER 4096

#include <stdio.h>
#include <stdlib.h>

static char * working_dir = {getenv("HOME")};
static FILE * working_file;
static char file_contents[FILE_BUFFER];
static char page_count[PAGE_COUNT_BUFFER];
static int i;
static int j;
static char ch;
