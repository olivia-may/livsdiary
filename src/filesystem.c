/* (C) 2022 Olivia May GPLv3+ */

#include "livsdiary.h"
#include "converters.h"
#include "time.h"
#include "filesystem.h"

int main()
{
	printf("** filesystem.c **\n");
	
	// `working_dir` should always be '~/.livsdiary'

	init();
	
	printf("%s\n", PAGE_COUNT_DIR);
	printf("%s\n", CURRENT_PAGE_DIR);
	printf("%s\n", DUMMY_FILE_DIR);
	printf("%s\n", PAGE_TIMES_DIR);
	
	check_dirs_and_files();
	copy_file_to_memory(PAGE_COUNT_DIR);
	copy_file_to_memory(PAGE_TIMES_DIR);

	// check page counter file
	printf("increment_page_count\n");
	increment_page_count();
	increment_page_count();
	
	printf("decrement_page_count\n");
	decrement_page_count();	
	decrement_page_count();	

	make_new_page();
	make_new_page();
	make_new_page();
	make_new_page();

	remove_most_recent_page();

	return 0;
}
