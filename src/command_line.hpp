/* (C) 2022 Olivia May GPLv3+ */

#include <iostream>
#include <string.h>

static Page working_page;

void invalid(char *argv)
{
	printf("Invalid argument: '%s'\n", argv);
}

void no_arg()
{
	printf("error: no arguments ('--help' for more info)\n");
}

void version()
{
	printf("LIVSDiary %s - (LI)ghtweight (V)irtual (S)imple Diary\n", PROGRAM_VERSION);
	printf("Copyright (C) 2022 Olivia May.\n");
	printf("License GPLv3+, this is free software.\n\n");
	printf("Written in C/C++ by Olivia May.\n");
}

void help()
{
	printf("A command line virtual diary.\n");
	printf("-h,			--help		show this menu\n");
	printf("			--version	show version\n");
	printf("-n,			--new		new page\n");
	printf("-e [page number],	--edit NUMBER	edit page. No input assumes most recent page\n");
	printf("-- WIP --\n");
	printf("-l,			--list		list all pages\n");
	printf("-v [page number],	--view NUMBER	view page\n");
	printf("-r			--remove	removes most recent page\n");
}

void edit(char page_num[])
{
	working_page.print_help();
	strcpy(working_page.page_num, page_num);
	working_page.edit();
}

void command_logic(int argc, char *argv[]) 	
{
	// puts most recent page number in `file_contents` 
	copy_file_to_memory(PAGE_COUNT_DIR);

	if (argc == 1) 
	{
		edit(file_contents);
	}
	else
	{
		if (strncmp(argv[1], "-h", 3) == 0 ||
		strncmp(argv[1], "--help", 7) == 0)
		{
			help();
		} 
		else if (strncmp(argv[1], "--version", 10) == 0)
		{
			version();
		}
		// fix issue: putting 0 gives a segmentation fault and
		// it also says negative numbers arent integers which is embarrasing
		// *sob*
		else if (strncmp(argv[1], "-e", 3) == 0 ||
		strncmp(argv[1], "--edit", 7) == 0)
		{
			if (argc == 2)
			{
				edit(file_contents);
			}
			else
			{
				if (check_input_is_int(argv[2]) == true)
				{
					int argv2_int = convert_to_int(argv[2]);
					if (argv2_int <= convert_to_int(file_contents)
					&& argv2_int >= 0)
					{ edit(argv[2]); }
					else
					{
						printf("error: found no page with number '%s'\n", argv[2]);
					}
				}
				else
				{
					invalid(argv[2]);
				}
			}
		}
		else if (strncmp(argv[1], "-n", 3) == 0 ||
		strncmp(argv[1], "--new", 6) == 0)
		{
			make_new_page();
		}
		else if (strncmp(argv[1], "-r", 3) == 0 ||
		strncmp(argv[1], "--remove", 9) == 0)
		{
			if (page_count[0] == '1' && page_count[1] == '\0') 
			{
				printf("error: refusing to remove first page!\n");
			}
			else
			{
				remove_most_recent_page();
			}
		}
		else
		{
			invalid(argv[1]);
		}
	}
}
