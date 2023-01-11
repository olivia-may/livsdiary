/* (C) 2022 Olivia May GPLv3+ */

#include "filesystem.h"

int main()
{
	printf("** filesystem.c **\n");
	
	// `working_dir` should always be the user's home directory

	printf("is_run_first_time() = %b\n", is_run_first_time());
	printf("is_run_first_time() %s\n", working_dir);


	check_dirs_and_files();
	printf("check_dirs_and_files() %s\n", working_dir);
	
	make_needed_dirs();
	printf("make_needed_dirs() %s\n", working_dir);
	
	make_needed_files();
	printf("make_needed_files() %s\n", working_dir);
	
	is_run_first_time();
	printf("is_run_first_time() %s\n", working_dir);
	
	printf("get_page_count() returns =  %s\n", get_page_count());
	printf("get_page_count() %s\n", working_dir);
	
	increment_page_count();
	printf("increment_page_count() %s\n", working_dir);	

	make_new_page();
	printf("make_new_page() %s\n", working_dir);

	increment_page_count();	
	printf("increment_page_count() %s\n", get_page_count());
	printf("increment_page_count() %s\n", working_dir);
	increment_page_count();	
	printf("increment_page_count() %s\n", get_page_count());
	printf("increment_page_count() %s\n", working_dir);
	increment_page_count();		
	printf("increment_page_count() %s\n", get_page_count());
	printf("increment_page_count() %s\n", working_dir);

	make_new_page();
	printf("make_new_page() %s\n", working_dir);
	make_new_page();
	printf("make_new_page() %s\n", working_dir);
	make_new_page();
	printf("make_new_page() %s\n", working_dir);

	return 0;
}
