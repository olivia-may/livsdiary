/* (C) 2022 Olivia May GPLv3+ */

#include <stdio.h>

#include "livsdiary.h"
#include "converters.h"
#include "time.h"

int main()
{
	init();

	printf("** time.c **\n");

	printf("get_current_time = %s\n", get_current_time());
	printf("get_page_time = %s\n", get_page_time("1"));
	
	return 0;
}
