/* (C) 2022 Olivia May GPLv3+ */

#include <stdio.h>
#include <time.h>

char * get_current_time()
{
	time_t now = time(0);
	char * dt = ctime(&now);
	return dt;
}

char * get_page_time(char * page_num)
{
	working_file = fopen(PAGE_TIMES_DIR, "r");
	static char page_time[TIMES_STORAGE_BUFFER];

	int num_of_new_lines = 0;
	i = 0;
	while (true)
	{
		ch = fgetc(working_file);
		if (ch == -1) { break; }		
		page_time[i] = ch;
		i++;

		if (ch == '\n')
		{
			num_of_new_lines++;
			if (num_of_new_lines == convert_to_int(page_num)) { break; }
			else { i = 0; }
		}
	}
	page_time[i] = '\0';

	return page_time;
}
