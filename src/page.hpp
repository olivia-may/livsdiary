/* (C) 2022 Olivia May GPLv3+ */ 

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

class Page
{
	private:
		char input[INPUT_BUFFER];
		int input_len = 0;
		char * page_time;
		bool save_input;
		bool stop_loop_here;
		bool is_making_new_page;
		bool is_opening_page;
		
		void get_file_location();
		void input_commands();
		void save_input_to_memory();
		void output();
		void write();
		void get_input_for_opening_pages();
		void process_input();
	public:
		char page_num[PAGE_COUNT_BUFFER];

		void edit();
};

void Page::save_input_to_memory()
{	
	save_input = true;
	if (input_len > 0)
	{
		if (input[0] == '`')
		{
			save_input = false;
			for (i = 0; i < input_len; i++)
			{
				if (input[i] == '`')
				{
					file_contents[strlen(file_contents) - 1] = '\0';
				}
			}
		}
	}
	
	if (save_input == true)
	{
		input[input_len] = '\n';
		input[input_len + 1] = '\0';
		strcat(file_contents, input);
	}
}

void Page::output()
{
	// removes 'cin''s output with ANSI escape codes. and also my debug 'cout's haha 
	cout << "\x1b[1A"; cout << "\x1b[2K";
	cout << "** Page " << page_num << " **" << endl;
	cout << page_time << "---" << endl;
	cout << file_contents << "<" << endl;
	cout << "\x1b[2L";
}

void Page::write()
{
	working_file = fopen(CURRENT_PAGE_DIR, "w");
	fprintf(working_file, file_contents);
	cout << "** Page " << page_num << " **" << endl;
	cout << page_time << "---" << endl;
	cout << file_contents << "<" << endl;
	cout << "\"~/.livsdiary/pages/" << page_num << "\" written" << endl;
}

bool check_input_is_int(char * input)
{
	for (i = 0; i < strlen(input); i++)
	{				
		if (input[i] == '0' ||
		input[i] == '1' ||
		input[i] == '2' ||
		input[i] == '3' ||
		input[i] == '4' ||
		input[i] == '5' ||
		input[i] == '6' ||
		input[i] == '7' ||
		input[i] == '8' ||
		input[i] == '9')
		{ continue; }
		else
		{ return false; }
	}

	return true;
}

void Page::get_input_for_opening_pages()
{
	j = 0;
	for (i = 2; i < input_len; i++)
	{
		if (input[i] == ' ')
		{
			cout << "found a space\n";
		}
		else
		{
			cout << "input i = " << input[i] << endl;
			input[j] = input[i];
			j++;
		}
	}
	cout << "input i - 3 = " << input[i] << endl;
	input[i - 3] = '\0';
	cout << "input test 0 " << input << endl;
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
				{
					write(); 
					break;
				}
			}
			if (input_len >= 2)
			{
				if ( input[1] == 'q' )
				{
					break;
				}
				if ( input[1] == 'w' )
				{
					write();
					stop_loop_here = true;
				}
				if ( input[1] == 'n' )
				{
					is_making_new_page = true;
					break;
				}
				if ( input[1] == 'e' )
				{
					is_opening_page = true;
					break;
				}
			}
		}

		if (stop_loop_here == false)
		{
			save_input_to_memory();
			output();
		}
	}
}

void Page::edit()
{
	while (true)
	{	
		is_making_new_page = false;
		is_opening_page = false;

		page_time = get_page_time(page_num);
		strcat(CURRENT_PAGE_DIR, page_num);
		copy_file_to_memory(CURRENT_PAGE_DIR);
		
		cout << "** Page " << page_num << " **" << endl;
		cout << page_time << "---" << endl;
		cout << file_contents << "<" << endl;
	
		process_input();
		
		if (is_making_new_page == true)
		{
			make_new_page();
			copy_file_to_memory(PAGE_COUNT_DIR);
			strcpy(page_num, file_contents); // switch to new page in cli
			CURRENT_PAGE_DIR[strlen(CURRENT_PAGE_DIR) - strlen(page_num)];
		}
		else if (is_opening_page == true)
		{
			get_input_for_opening_pages();
			cout << "input check 1 = " << input << endl;
			if (check_input_is_int(input) == true)
			{
				cout << "is an integer" << endl;
				cout << "strlen(input) = " << strlen(input) << endl;
				copy_file_to_memory(PAGE_COUNT_DIR);

				// check if that page exists
				if (convert_to_int(input) <=
				convert_to_int(file_contents))
				{
					strcpy(page_num, input); // phew, open this page
					cout << page_num << endl;
					continue;
				}
				else
				{
					cout << "error: no page with number '" << input <<
					"'" << endl;
				}
			}	
			else
			{
				cout << "error: '" << input << "' is not an integer" << endl;
			}
		}
		else
		{
			break;
		}
	}
}
