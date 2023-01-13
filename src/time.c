/* (C) 2022 Olivia May GPLv3+ */

#include <stdio.h>

#include "livsdiary.h"
#include "converters.h"
#include "time.h"

int main()
{
	printf("** time.c **\n");

	printf("get_current_time = %s\n", get_current_time());
	printf("get_page_time = %s\n", get_page_time("1"));
	printf("working_dir = %s\n", working_dir);
	
	return 0;
}
