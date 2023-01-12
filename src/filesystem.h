/* (C) 2022 Olivia May GPLv3+ */

#include <sys/stat.h>
#include <unistd.h>

#include "time.h"

bool is_run_first_time()
{
	if (access(working_dir, F_OK) == 0)
	{
		// '~/.livsdiary/'
		working_dir[strlen(working_dir) - 10] = '\0';
		return false;
	}
	else
	{	
		// goes to `make_needed_dirs()`
		working_dir[strlen(working_dir) - 11] = '\0';
		return true;	
	}
}

void make_needed_dirs()
{
	mkdir(working_dir, 0777);
	strcat(working_dir, "/pages"); mkdir(working_dir, 0777);
	working_dir[strlen(working_dir) - 5] = '\0';
	strcat(working_dir, "info"); mkdir(working_dir, 0777);	
}

void make_needed_files()
{
	strcat(working_dir, "/page_counter");
	working_file = fopen(working_dir, "w");
	working_dir[strlen(working_dir) - 12] = '\0';
	fprintf(working_file, "0");
	fclose(working_file);
	
	strcat(working_dir, "times");
	working_file = fopen(working_dir, "w");
	working_dir[strlen(working_dir) - 5] = '\0';
	fclose(working_file);

	// always do last
	strncat(working_dir, "dummy", 7);
	working_file = fopen(working_dir, "w");
	fclose(working_file);

	// working_dir should be '~/.livsdiary/' when function is done using it
	// No spaghetti code!
	working_dir[strlen(working_dir) - 10] = '\0';
}

char * get_page_count()
{
	working_file = fopen(working_dir, "r");

	static char page_count_string[PAGE_COUNT_BUFFER];
	char ch;
	i = 0;
	while (true)
	{
		ch = fgetc(working_file);
		if (ch == -1) { break; }
		page_count_string[i] = ch;
		i++;
	}
	page_count_string[i] = '\0';
	
	fclose(working_file);

	return page_count_string;
}

void increment_page_count()
{
	int page_count = convert_to_int(get_page_count()) + 1;
	FILE *page_counter_file = fopen(working_dir, "w");

	fprintf
	(
		page_counter_file, 
		convert_to_char_array(page_count)
	);

	fclose(page_counter_file);
}

void make_new_page()
{
	strcat(working_dir, "info/page_counter");
	increment_page_count();
	char * page_count = get_page_count();
	
	working_dir[strlen(working_dir) - 17] = '\0';
	strcat(strcat(working_dir, "pages/"), page_count);
	FILE *new_page_file = fopen(working_dir, "w");
	fclose(new_page_file);
	working_dir[strlen(working_dir) - 6 - strlen(page_count)] = '\0';
	
	// put the time the page was created in '~/.livsdiary/info/times'
	strcat(working_dir, "info/times");
	FILE *new_page_time_file = fopen(working_dir, "a");
	fprintf(new_page_time_file, get_current_time());
	fclose(new_page_time_file);
	// '~/.livsdiary/'
	working_dir[strlen(working_dir) - 10] = '\0';
}

void check_dirs_and_files()
{
	strcat(working_dir, "/.livsdiary/info/dummy");
	if (is_run_first_time() == true)
	{
		make_needed_dirs();
		make_needed_files();
		make_new_page();
	}
}

char * copy_file_to_memory(char * dir)
{
	FILE * file = fopen(dir, "r");
	printf("1\n");
	static char file_contents[PAGE_BUFFER];
	printf("2\n");
	char ch;
	printf("3\n");

	i = 0;
	printf("4\n");
	while (true)
	{
		ch = fgetc(file);
		printf("ch = %c\n", ch);
		// not sure if this is safe, oh well
		if (ch == -1)
		{ 
			file_contents[i] = '\0';
			break;
		}
		
		file_contents[i] = ch;
		printf("file-contents[i] = %c\n", file_contents[i]);

		i++;
	}

	printf("5\n");
	fclose(file);
	return file_contents;
}

void decrement_page_count()
{
	int page_count = convert_to_int(get_page_count()) - 1;
	FILE *page_counter_file = fopen(working_dir, "w");

	fprintf
	(
		page_counter_file, 
		convert_to_char_array(page_count)
	);

	fclose(page_counter_file);
}

void remove_most_recent_page()
{	
	strcat(working_dir, "info/page_counter");
	char * page_count = get_page_count();
	
	decrement_page_count();
	
	// remove 1 line from the 'times' file
	working_dir[strlen(working_dir) - 12] = '\0';
	strcat(working_dir, "times");
	printf(working_dir);
	char * page_time_file_contents = copy_file_to_memory(working_dir);
	page_time_file_contents[strlen(page_time_file_contents) - 25] = '\0';
	FILE * page_time_file = fopen(working_dir, "w");
	fprintf(page_time_file, page_time_file_contents);
	
	working_dir[strlen(working_dir) - 10] = '\0';
	strcat(strcat(working_dir, "pages/"), page_count);
	remove(working_dir); // remove file

	//fclose(page_time_file);
	working_dir[strlen(working_dir) - 6 - strlen(page_count)] = '\0';
	printf(working_dir);
}
