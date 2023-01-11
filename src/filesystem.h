/* (C) 2022 Olivia May GPLv3+ */

#include <sys/stat.h>
#include <unistd.h>

#include "time.h"

#define PAGE_BUFFER 4096
#define INPUT_BUFFER 128

void make_needed_dirs()
{
	strcat(working_dir, "/.livsdiary"); mkdir(working_dir, 0777);
	strcat(working_dir, "/pages"); mkdir(working_dir, 0777);
	working_dir[strlen(working_dir) - 5] = '\0';
	strncat(working_dir, "info", 5); mkdir(working_dir, 0777);
	
	// working_dir should be '~' when function is done using it
	// No spaghetti code!
	working_dir[strlen(working_dir) - 16] = '\0';
}

void make_needed_files()
{
	strcat(working_dir, "/.livsdiary/info/page_counter");
	FILE *page_counter = fopen(working_dir, "w");
	working_dir[strlen(working_dir) - 12] = '\0';
	fprintf(page_counter, "0\n");
	fclose(page_counter);
	
	strcat(working_dir, "times");
	FILE *times = fopen(working_dir, "w");
	working_dir[strlen(working_dir) - 5] = '\0';
	fclose(times);

	// always do last
	strncat(working_dir, "dummy", 7);
	FILE *dummy = fopen(working_dir, "w");
	fclose(dummy);

	// '~'
	working_dir[strlen(working_dir) - 22] = '\0';
}

bool is_run_first_time()
{
	strcat(working_dir, "/.livsdiary/info/dummy");
	if (access(working_dir, F_OK) == 0)
	{
		working_dir[strlen(working_dir) - 22] = '\0';
		return false;
	}
	else
	{
		working_dir[strlen(working_dir) - 22] = '\0';
		return true;	
	}
}

char * get_page_count()
{
	strcat(working_dir, "/.livsdiary/info/page_counter");
	FILE *page_counter_file = fopen(working_dir, "r");

	static char page_count_string[8];
	int i = 0;
	char ch;
	while (true)
	{
		ch = fgetc(page_counter_file);
		if (ch == -1) { break; }
		page_count_string[i] = ch;
		i++;
	}
	page_count_string[i] = '\0';
	
	working_dir[strlen(working_dir) - 29] = '\0';
	fclose(page_counter_file);

	return page_count_string;
}

void increment_page_count()
{
	int page_count = convert_to_int(get_page_count()) + 1;
	strcat(working_dir, "/.livsdiary/info/page_counter");
	FILE *page_counter_file = fopen(working_dir, "w");

	fprintf
	(
		page_counter_file, 
		convert_to_char_array(page_count)
	);

	working_dir[strlen(working_dir) - 29] = '\0';
	fclose(page_counter_file);
}

void make_new_page()
{
	increment_page_count();
	
	char * page_count = get_page_count();
	strcat
	(
		strcat
		(
			working_dir,
		 	"/.livsdiary/pages/"
		),
		page_count
	);

	FILE *new_page_file = fopen(working_dir, "w");
	fclose(new_page_file);
	working_dir[strlen(working_dir) - 6 - strlen(page_count)] = '\0';
	
	// put the time the page was created in '~/.livsdiary/info/times'
	strcat(working_dir, "info/times");
	FILE *new_page_time_file = fopen(working_dir, "a");
	fprintf(new_page_time_file, get_current_time());
	fclose(new_page_time_file);
	// `working_dir` = '~'
	working_dir[strlen(working_dir) - 22] = '\0';
}

void check_dirs_and_files()
{
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

	int i = 0;
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
	return file_contents;
}

void decrement_page_count()
{
	int page_count = convert_to_int(get_page_count()) - 1;
	strcat(working_dir, "/.livsdiary/info/page_counter");
	FILE *page_counter_file = fopen(working_dir, "w");

	fprintf
	(
		page_counter_file, 
		convert_to_char_array(page_count)
	);

	working_dir[strlen(working_dir) - 29] = '\0';
	fclose(page_counter_file);
}

void remove_most_recent_page()
{
	char * page_count = get_page_count();
	strcat
	(
		strcat
		(
			working_dir,
		 	"/.livsdiary/pages/"
		),
		page_count
	);
	remove(working_dir); // remove file

	working_dir[strlen(working_dir) - 18 - strlen(page_count)] = '\0';
	decrement_page_count();

	// remove 1 line from the 'times' file
	strcat(working_dir, "/.livsdiary/info/times");
	char * page_time_file_contents = copy_file_to_memory(working_dir);
	page_time_file_contents[strlen(page_time_file_contents) - 25] = '\0';
	FILE * page_time_file = fopen(working_dir, "w");
	fprintf(page_time_file, page_time_file_contents);

	fclose(page_time_file);
	working_dir[strlen(working_dir) - 22] = '\0';
}
