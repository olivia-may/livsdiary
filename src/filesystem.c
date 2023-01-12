/* (C) 2022 Olivia May GPLv3+ */

#include "filesystem.h"

int main()
{
	printf("** filesystem.c **\n");
	
	// `working_dir` should always be '~/.livsdiary'

	check_dirs_and_files();
	printf("check_dirs_and_files() %s\n", working_dir);	
	
	make_new_page();
	printf("make_new_page() %s\n", working_dir);
	make_new_page();
	printf("make_new_page() %s\n", working_dir);
	make_new_page();
	printf("make_new_page() %s\n", working_dir);
	make_new_page();
	printf("make_new_page() %s\n", working_dir);

	remove_most_recent_page();
	printf("remove_most_recent_page() %s\n", working_dir);

	return 0;
}
