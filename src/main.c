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

#include "commands.h"
#include "config.h"
#include "editor.h"
#include "filesystem.h"

/* The command-line options */
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

    // so it can be free'd
    char *page_num_str_clone = NULL; 
    page_num_str_clone = malloc(sizeof(char) * (strlen(page_num_str) + 1));
    strcpy(page_num_str_clone, page_num_str);

    editor_enter();
    editor_open_page(page_num_str_clone);
    editor_exit();
}
void view(char *page_num_str) {
    char *page_loc = NULL;
    char *page_contents = NULL;

    page_loc = get_page_loc(page_num_str);
    page_contents = get_file_contents(page_loc);
    printf("%s\n", page_contents);

    free(page_loc);
    free(page_contents);
}
void list_pages() {
    unsigned int page_count = get_page_count();
    char *i_str = NULL;
    for (unsigned int i = 0; i <= page_count; i++) {
        i_str = convert_to_char_array(i);
        view(i_str);
        free(i_str);
    }
}

void print(char *str) {
    printf("%s\n", str);
    free(str);
}

int main(int argc, char **argv) {
    unsigned int newest_page_num;
    char *newest_page_num_str = NULL;

    initialize_locs();
    if (access(page_count_loc, F_OK) != 0) initialize_diary();
    newest_page_num = get_page_count();
    newest_page_num_str = convert_to_char_array(newest_page_num);

    if (argc == 1) edit(newest_page_num_str);
    else {
    if (strncmp(argv[1], "-h", 3) == 0
    || strncmp(argv[1], "--help", 7) == 0) help();
    else if (strncmp(argv[1], "-V", 3) == 0
    || strncmp(argv[1], "--version", 10) == 0) version();

    else if (strncmp(argv[1], "-e", 3) == 0) {
        if (argc == 2) edit(newest_page_num_str);
        else switch (is_page_num_found(argv[2])) {
            case PAGE_FOUND: edit(argv[2]); break;
            case NO_PAGE_FOUND:
            print(get_page_not_found_str(argv[2])); break;
            case INVALID_INPUT:
            print(get_invalid_page_str(argv[2])); break;
        }
    }
    else if (strncmp(argv[1], "-v", 3) == 0) {
        if (argc == 2) view(newest_page_num_str);
        else switch (is_page_num_found(argv[2])) {
            case PAGE_FOUND: view(argv[2]); break;
            case NO_PAGE_FOUND:
            print(get_page_not_found_str(argv[2])); break;
            case INVALID_INPUT:
            print(get_invalid_page_str(argv[2])); break;
        }
    }

    // 7 because not checking for null char at the end
    else if (strncmp(argv[1], "--edit=", 7) == 0) {
        switch (is_page_num_found(&argv[1][7])) {
            case PAGE_FOUND: edit(&argv[1][7]); break;
            case NO_PAGE_FOUND:
            print(get_page_not_found_str(&argv[1][7])); break;
            case INVALID_INPUT:
            print(get_invalid_page_str(&argv[1][7])); break;
        }
    }
    else if (strncmp(argv[1], "--view=", 7) == 0) {
        switch (is_page_num_found(&argv[1][7])) {
            case PAGE_FOUND: view(&argv[1][7]); break;
            case NO_PAGE_FOUND:
            print(get_page_not_found_str(&argv[1][7])); break;
            case INVALID_INPUT:
            print(get_invalid_page_str(&argv[1][7])); break;
        }
    }

    else if (strncmp(argv[1], "-n", 3) == 0
    || strncmp(argv[1], "--new", 6) == 0) make_new_page();
    else if (strncmp(argv[1], "-r", 3) == 0
    || strncmp(argv[1], "--remove", 9) == 0) {
        if (newest_page_num == 0) 
        printf("error: refusing to remove Table of Contents!\n");
        else remove_newest_page();
    }
    else if (strncmp(argv[1], "-l", 3) == 0
    || strncmp(argv[1], "--list", 7) == 0) list_pages();
    else print(get_invalid_arg_str(argv[1], COMMAND_LINE));
    }

    free(newest_page_num_str);
    free_locs();
    return 0;
}
