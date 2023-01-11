/* (C) 2022 Olivia May GPLv3+ */

#include <stdio.h>

#include "filesystem.h"

int main()
{
	printf("** time.c **\n");

	printf("get_current_time = %s\n", get_current_time());

	for (int i = 1; i < convert_to_int(get_page_count()); i++)
	{
		printf("get_page_time = %s\n", get_page_time(convert_to_char_array(i)));
		printf("working_dir = %s\n", working_dir);
	}
	
	return 0;
}
