/*
 * LIVSDiary - (LI)ghtweight (V)irtual (S)imple Diary
 * Copyright (C) 2022 Olivia May - olmay@tuta.io
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <cstring>

#include "converters.h"
#include "filesystem.h"
#include "page.hpp"

void Page::save_input_to_memory()
{
	save_input = true;
	if (input_len > 0)
	{
		if (input[0] == '`')
		{
			save_input = false;
			for (int i = 0; i < input_len; i++)
			{
				if (input[i] == '`')
				{ page_mem_storage[strlen(page_mem_storage) - 1] = '\0'; }
			}
		}
	}
	
	if (save_input == true)
	{
		input[input_len] = '\n';
		input[input_len + 1] = '\0';
		strcat(page_mem_storage, input);
	}
}

void Page::output()
{
	// removes `cin`'s output with ANSI escape codes. and also my debug `cout`s haha 
	cout << "\x1b[1A"; cout << "\x1b[2K";
	cout << page_mem_storage << "<" << endl;
	cout << "\x1b[2L";
}

void Page::write()
{
	FILE * current_page_file = fopen(page_loc, "w");
	fprintf(current_page_file, page_mem_storage);
	fclose(current_page_file);
	cout << "\"~/.livsdiary/pages/" << page_num << "\" written" << endl << endl;
}


void Page::get_input_for_opening_pages()
{
	int j = 0;
	int i;
	for (i = 2; i < input_len; i++)
	{
		if (input[i] == ' ') {}
		else
		{
			input[j] = input[i];
			j++;
		}
	}
	input[i - 3] = '\0';
}

void Page::print_help()
{
	printf("Use:\n");
	printf(":e NUMBER	open NUMBER page\n");
	printf(":h		show this menu\n");
	printf(":n		make new page and switch to it\n");
	printf(":q		quit\n");
	printf(":r		remove most recent page, be careful\n");
	printf(":w		write to page file\n");
	printf(":wq		write and quit\n");
	printf("\n");
	printf("'<' is where you are writing.\n");
	printf("Use '`' to backspace. You can use multiple like this \"```\".\n");
	printf("Start typing!\n");
	printf("\n");
}

void Page::process_input()
{
	while (true)
	{
		stop_loop_here = false;

		cin.getline(input, INPUT_BUFFER);
		input_len = strlen(input);
		
		if (input[0] == ':')
		{
			if (input_len == 3)
			{
				if (input[1] == 'w' && input[2] == 'q')
				{ write(); break; }
			}
			if (input_len >= 2)
			{
				if (input[1] == 'q')
				{ break; }
				if (input[1] == 'w')
				{
					write();
					output();
					stop_loop_here = true;
				}
				if (input[1] == 'n')
				{ is_making_new_page = true; break; }
				if (input[1] == 'e')
				{ is_opening_page = true; break; }
				if (input[1] == 'r')
				{ is_removing_page = true; break; }
				if (input[1] == 'h')
				{
					print_help();
					cout << endl;
					output();
					stop_loop_here = true;
				}
			}
		}

		if (stop_loop_here == false)
		{ save_input_to_memory(); output(); }
	}
}

void Page::edit()
{	
	while (true)
	{	
		is_making_new_page = false;
		is_opening_page = false;
		is_removing_page = false;

		strcat(page_loc, page_num);
		page_mem_storage = copy_file_to_memory(page_loc);

		cout << page_mem_storage << "<" << endl;

		process_input();
		
		if (is_making_new_page == true)
		{
			page_loc[strlen(page_loc) - strlen(page_num)] = '\0';
			make_new_page();
			page_num = copy_file_to_memory(PAGE_COUNT_DIR); // switch to new page in cli
		}
		else if (is_removing_page == true)
		{
			page_loc[strlen(page_loc) - strlen(page_num)] = '\0';
			int page_count_int = convert_to_int(copy_file_to_memory(PAGE_COUNT_DIR));
			stop_loop_here = false;
			if (page_count_int == 0)
			{
				cout << "error: cannot remove Table of Contents!" << endl;
				stop_loop_here = true;
			}

			if (stop_loop_here == false)
			{
				// change to older page if you deleted the current 
				// working page
				if (convert_to_int(page_num) == page_count_int)
				{ page_num = convert_to_char_array(page_count_int - 1); }

				remove_most_recent_page();
			}
		}
		else if (is_opening_page == true)
		{
			page_loc[strlen(page_loc) - strlen(page_num)] = '\0';
			get_input_for_opening_pages();
			if (check_input_is_int(input) == true)
			{
				int input_int = convert_to_int(input);
				// check if that page exists
				if (input_int <= convert_to_int(copy_file_to_memory(PAGE_COUNT_DIR))
				&& input_int >= 0)
				{ strcpy(page_num, input); // phew, open this page
				}
				else
				{ cout << "error: no page with number '" << input << "'" << endl; }
			}
			else
			{ cout << "error: '" << input << "' is invalid" << endl; }
		}
		else
		{ break; }
	}
}
