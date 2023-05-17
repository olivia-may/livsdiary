/*
 * LIVSDiary - (LI)ghtweight (V)irtual (S)imple Diary
 * Copyright (C) 2022 Olivia May - olivia.may@tuta.io
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

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "converters.h"
#include "editor.h"
#include "filesystem.h"
#include "config.h"

/* The command-line options */
void invalid(char *argv) {
	printf("Invalid argument: '%s', try '--help'\n", argv);
}
void version() {
	printf("LIVSDiary %s - (LI)ghtweight (V)irtual (S)imple Diary\n", VERSION);
	printf("Copyright (C) 2022 Olivia May.\n");
	printf("License GPLv3+, this is free software.\n\n");
	printf("Written in C by Olivia May.\n");
}
void help() {
	printf("A command line virtual diary.\n");
	printf("-e [page number],	--edit=NUMBER	edit page. No input assumes most recent page\n");
	printf("-h,			--help		show this menu\n");
	printf("-l,			--list		list all pages\n");
	printf("-n,			--new		new page\n");
	printf("-r			--remove	removes most recent page\n");
	printf("-v [page number],	--view=NUMBER	view page\n");
	printf("-V			--version	show version\n");
}
void edit(char *page_num_str) {
	/*
	printf("** LIVSDiary %s **\n", PROGRAM_VERSION);
	printf("This program comes with ABSOLUTELY NO WARRANTY.\n");
	printf("This is free software, and you are welcome to\n");
	printf("redistribute it under certain conditions.\n\n");
	*/
    editor_enter();
    editor_open_page(page_num_str);
    editor_exit();
}
void view(char *page_num_str) {
	char *page_loc = NULL; page_loc = loc_malloc();
    strcpy(page_loc, get_diary_dir());
	strcat(page_loc, page_num_str);
	printf("%s\n", get_file_contents(page_loc));

    free(page_loc);
}
void list_pages() {
    unsigned int page_count = get_page_count();
    for (int i = 0; i <= page_count; i++)
    view(convert_to_char_array(i));
}

int main(int argc, char **argv) {
	if (access(get_page_counter_loc(), F_OK) != 0) initialize_diary();
    unsigned int newest_page_num = get_page_count();

	if (argc == 1) edit(convert_to_char_array(newest_page_num));
	else {
		if (strncmp(argv[1], "-h", 3) == 0 ||
		strncmp(argv[1], "--help", 7) == 0) help();

		else if (strncmp(argv[1], "-V", 3) == 0 ||
		strncmp(argv[1], "--version", 10) == 0) version();

		else if (strncmp(argv[1], "-e", 3) == 0) {
			if (argc == 2) edit(convert_to_char_array(newest_page_num));

			else {
				if (check_input_is_int(argv[2]) == true) {
					int argv2_int = convert_to_int(argv[2]);
					if (argv2_int <= newest_page_num
					&& argv2_int >= 0) edit(argv[2]);
					else printf("error: found no page with number '%s'\n", argv[2]);
				}
				else invalid(argv[2]);
			}
		}
		else if (strncmp(argv[1], "-v", 3) == 0) {
			if (argc == 2) view(convert_to_char_array(newest_page_num));
			else {
				if (check_input_is_int(argv[2]) == true) {
					int argv2_int = convert_to_int(argv[2]);
					if (argv2_int <= newest_page_num
					&& argv2_int >= 0) view(argv[2]);
					else printf("error: found no page with number '%s'\n", argv[2]);
				}
				else invalid(argv[2]);
			}
		}

		// 7 because not checking for null char at the end
		else if (strncmp(argv[1], "--edit=", 7) == 0) {
			int i;
			for (i = 7; i < strlen(argv[1]); i++)
            argv[1][i - 7] = argv[1][i];
			argv[1][i - 7] = '\0';
			
			if (argv[1][0] == '\0') invalid(argv[1]);
			else if (check_input_is_int(argv[1]) == true) {
				int argv2_int = convert_to_int(argv[1]);
				if (argv2_int <= convert_to_int(convert_to_char_array(newest_page_num))
				&& argv2_int >= 0) edit(argv[1]);
				else printf("error: found no page with number '%s'\n", argv[1]);
			}
			else invalid(argv[1]);
		}

		else if (strncmp(argv[1], "--view=", 7) == 0) {
			int i;
			for (i = 7; i < strlen(argv[1]); i++)
			argv[1][i - 7] = argv[1][i];
			argv[1][i - 7] = '\0';
			
			if (argv[1][0] == '\0') invalid(argv[1]);
			else if (check_input_is_int(argv[1]) == true) {
				int argv2_int = convert_to_int(argv[1]);
				if (argv2_int <= convert_to_int(convert_to_char_array(newest_page_num))
				&& argv2_int >= 0) view(argv[1]);
				else printf("error: found no page with number '%s'\n", argv[1]);
			}
			else invalid(argv[1]);
		}

		else if (strncmp(argv[1], "-n", 3) == 0 ||
		strncmp(argv[1], "--new", 6) == 0) make_new_page();

		else if (strncmp(argv[1], "-r", 3) == 0 ||
		strncmp(argv[1], "--remove", 9) == 0) {
			if (newest_page_num == 0) 
			printf("error: refusing to remove Table of Contents!\n");
			else remove_newest_page();
		}
		else if (strncmp(argv[1], "-l", 3) == 0 ||
		strncmp(argv[1], "--list", 7) == 0) list_pages();

		else invalid(argv[1]);
	}

	return 0;
}
