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

#include <time.h>

char * get_current_time()
{
	time_t now = time(0);
	char * dt = ctime(&now);
	return dt;
}

char * get_page_time(char * page_num)
{
	working_file = fopen(PAGE_TIMES_DIR, "r");
	static char page_time[TIMES_STORAGE_BUFFER];

	int num_of_new_lines = 0;
	int i = 0;
	while (true)
	{
		ch = fgetc(working_file);
		if (ch == -1) { break; }		
		page_time[i] = ch;
		i++;

		if (ch == '\n')
		{
			if (num_of_new_lines == convert_to_int(page_num)) { break; }
			else { i = 0; }
			num_of_new_lines++;
		}
	}
	page_time[i] = '\0';

	return page_time;
}
