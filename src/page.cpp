/* (C) 2022 Olivia May GPLv3+ */

#include "livsdiary.h"
#include "converters.h"
#include "time.h"
#include "filesystem.h"
#include "page.hpp"

int main()
{
	printf("** page.cpp **\n");

	check_dirs_and_files();
	
	printf("%s\n", working_dir);
	Page test;
	test.page_num = "1";
	printf("%s\n", test.page_num);
	test.edit();
	printf("%s\n", working_dir);
}
