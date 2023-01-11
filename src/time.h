/* (C) 2022 Olivia May GPLv3+ */

#include <time.h>
#include <stdio.h>

#include "variables.h"
#include "converters.h"

#define TIMES_STORAGE_BUFFER 64

char * get_current_time()
{
	time_t now = time(0);
	char * dt = ctime(&now);
	return dt;
}

char * get_page_time(char * page_num)
{
	int page_num_int = convert_to_int(page_num);
	strcat(working_dir, "/.livsdiary/info/times");
	FILE * times_storage_file = fopen(working_dir, "r");
	static char page_time[TIMES_STORAGE_BUFFER];

	int i = 0;
	int num_of_new_lines = 0;
	char ch;

	while (true)
	{
		ch = fgetc(times_storage_file);
		if (ch == -1) { break; }		
		page_time[i] = ch;
		i++;

		if (ch == '\n')
		{
			num_of_new_lines++;
			if (num_of_new_lines == page_num_int) { break; }
			else { i = 0; }
		}
	}

	page_time[i] = '\0';

	working_dir[strlen(working_dir) - 22] = '\0';
	
	return page_time;
}
