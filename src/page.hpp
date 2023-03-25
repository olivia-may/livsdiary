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

#ifndef PAGE_HPP
#define PAGE_HPP

#define INPUT_BUFFER 128

class Page
{
	private:
		char * page_mem_storage = NULL;
		char input[INPUT_BUFFER];
		char * page_loc = get_page_loc();
		int input_len = 0;
		bool save_input;
		bool stop_loop_here;
		bool is_making_new_page;
		bool is_opening_page;
		bool is_removing_page;
		
		void input_commands();
		void save_input_to_memory();
		void output();
		void write();
		void get_input_for_opening_pages();
		void process_input();
	public:
		char * page_num = NULL;

		void print_help();
		void edit();
};

#endif
