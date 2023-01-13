/* (C) 2022 Olivia May GPLv3+ */

#include <sys/stat.h>
#include <unistd.h>

// to `file_contents`
void copy_file_to_memory()
{
	working_file = fopen(working_dir, "r");
	i = 0;
	char ch;
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
	strcat(working_dir, "info"); mkdir(working_dir, 0777);	
}

void make_needed_files()
{
	strcat(working_dir, "/page_counter");
	working_file = fopen(working_dir, "w");
	fprintf(working_file, "0\0");
	working_dir[strlen(working_dir) - 12] = '\0';
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

// this feels kinda dumb but oh well
void increment_page_count()
{
	copy_file_to_memory();
	working_file = fopen(working_dir, "w");
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
	strcat(working_dir, "info/page_counter");
	increment_page_count();
	copy_file_to_memory();
	
	working_dir[strlen(working_dir) - 12] = '\0';
	strcat(working_dir, "times");
	working_file = fopen(working_dir, "a");
	fprintf(working_file, get_current_time());
	fclose(working_file);
	
	working_dir[strlen(working_dir) - 10] = '\0';
	strcat(strcat(working_dir, "pages/"), file_contents);
	working_file = fopen(working_dir, "w");
	working_dir[strlen(working_dir) - 6 - strlen(file_contents)] = '\0';
	fclose(working_file);
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

void decrement_page_count()
{
	copy_file_to_memory();
	working_file = fopen(working_dir, "w");
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
	strcat(working_dir, "info/page_counter");
	copy_file_to_memory();
	decrement_page_count();
	
	working_dir[strlen(working_dir) - 17] = '\0';
	strcat(strcat(working_dir, "pages/"), file_contents);
	remove(working_dir); // remove file
	
	// remove 1 line from the 'times' file
	working_dir[strlen(working_dir) - 6 - strlen(file_contents)] = '\0';
	strcat(working_dir, "info/times");
	copy_file_to_memory();
	file_contents[strlen(file_contents) - 25] = '\0';
	working_file = fopen(working_dir, "w");
	fprintf(working_file, file_contents);
	
	working_dir[strlen(working_dir) - 10] = '\0';
}
