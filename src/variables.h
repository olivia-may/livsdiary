/* (C) 2022 Olivia May GPLv3+ */

#include <stdlib.h>

#define PAGE_BUFFER 4096
#define INPUT_BUFFER 128
#define PAGE_COUNT_BUFFER 8

static char * working_dir = {getenv("HOME")};
static FILE * working_file;
static int i;
