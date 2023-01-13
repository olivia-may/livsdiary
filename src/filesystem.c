/* (C) 2022 Olivia May GPLv3+ */

#include "livsdiary.h"
#include "converters.h"
#include "time.h"
#include "filesystem.h"

int main()
{
	printf("** filesystem.c **\n");
	
	// `working_dir` should always be '~/.livsdiary'

	check_dirs_and_files();
	printf("check_dirs_and_files() %s\n", working_dir);

	strcat(working_dir, "info/page_counter");
	
	copy_file_to_memory();
	copy_file_to_memory();
	copy_file_to_memory();
	copy_file_to_memory();
	copy_file_to_memory();
	copy_file_to_memory();
	copy_file_to_memory();

	// check page counter file
	printf("increment_page_count\n");
	increment_page_count();
	increment_page_count();
	
	printf("decrement_page_count\n");
	decrement_page_count();	
	decrement_page_count();	

	working_dir[strlen(working_dir) - 17] = '\0';
	printf("%s\n", working_dir);

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
