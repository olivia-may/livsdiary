/* (C) 2022 Olivia May GPLv3+ */

#include <sys/stat.h>
#include <unistd.h>

// to `file_contents`
void copy_file_to_memory(char * dir)
{
	working_file = fopen(dir, "r");
	i = 0;
	while (true)
	{
		ch = fgetc(working_file);
		if (ch < 0) { break; }
		file_contents[i] = ch;
		i++;
	}
	file_contents[i] = '\0';
	fclose(working_file);
}

// checks if ~/.livsdiary/info/dummy exists
bool is_run_first_time()
{
	if (access(DUMMY_FILE_DIR, F_OK) == 0)
	{
		return false;
	}
	else
	{	
		return true;	
	}
}

void make_needed_dirs()
{	
	char * working_dir = getenv("HOME");
	strcat(working_dir, "/.livsdiary");
	mkdir(working_dir, 0777);
	strcat(working_dir, "/pages");
	mkdir(CURRENT_PAGE_DIR, 0777);
	working_dir[strlen(working_dir) - 5] = '\0';
	strcat(working_dir, "info");
	mkdir(working_dir, 0777);
}

void make_needed_files()
{
	working_file = fopen(PAGE_COUNT_DIR, "w");
	fprintf(working_file, "0\0");
	fclose(working_file);
	
	working_file = fopen(PAGE_TIMES_DIR, "w");
	fprintf(working_file, "Table of Contents\n");
	fclose(working_file);

	// always do last
	working_file = fopen(DUMMY_FILE_DIR, "w");
	fclose(working_file);
}

void make_toc_page()
{
	strcat(CURRENT_PAGE_DIR, "0");
	working_file = fopen(CURRENT_PAGE_DIR, "w");

	fprintf(working_file, "This page cannot be removed.\n");
	fprintf(working_file, "Feel free remove this message and\n");
	fprintf(working_file, "write anything you want here!\n");
	fprintf(working_file, "Type and enter ':n' to make a new diary entry.\n");

	fclose(working_file);
	CURRENT_PAGE_DIR[strlen(CURRENT_PAGE_DIR) - 1] = '\0';
}

// this feels kinda dumb but oh well
void increment_page_count()
{
	copy_file_to_memory(PAGE_COUNT_DIR);
	working_file = fopen(PAGE_COUNT_DIR, "w");
	fprintf
	(
		working_file, 
		convert_to_char_array
		(
			convert_to_int(file_contents) + 1
		)
	);
	fclose(working_file);
}

void make_new_page()
{
	increment_page_count();
	
	working_file = fopen(PAGE_TIMES_DIR, "a");
	fprintf(working_file, get_current_time());
	fclose(working_file);
	
	copy_file_to_memory(PAGE_COUNT_DIR);
	strcat(CURRENT_PAGE_DIR, file_contents);
	working_file = fopen(CURRENT_PAGE_DIR, "w");
	CURRENT_PAGE_DIR[strlen(CURRENT_PAGE_DIR) - strlen(file_contents)] = '\0';
	fclose(working_file);
}

void check_dirs_and_files()
{
	if (is_run_first_time() == true)
	{
		make_needed_dirs();
		make_needed_files();
		make_toc_page();
	}
}

void decrement_page_count()
{
	copy_file_to_memory(PAGE_COUNT_DIR);
	working_file = fopen(PAGE_COUNT_DIR, "w");
	fprintf
	(
		working_file, 
		convert_to_char_array
		(
			convert_to_int(file_contents) - 1
		)
	);
	fclose(working_file);
}

void remove_most_recent_page()
{	
	copy_file_to_memory(PAGE_COUNT_DIR);
	
	decrement_page_count();
	
	strcat(CURRENT_PAGE_DIR, file_contents);
	remove(CURRENT_PAGE_DIR); // remove file
	CURRENT_PAGE_DIR[strlen(CURRENT_PAGE_DIR)- strlen(file_contents)] = '\0';
	
	// remove 1 line from the 'times' file
	copy_file_to_memory(PAGE_TIMES_DIR);
	file_contents[strlen(file_contents) - 25] = '\0';
	working_file = fopen(PAGE_TIMES_DIR, "w");
	fprintf(working_file, file_contents);
	fclose(working_file);
}
