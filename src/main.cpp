/* 
 * LIVSDiary
 * (C) 2022 Olivia May - olmay@tuta.io GPLv3+
 *
 * (LI)ghtweight (V)irtual (S)imple Diary
 *
 * A program that should make a directory in the user's home folder. 
 * And be able to store a diary on the user's hard drive. Maybe also
 * in memory too when it runs. It will be a command line program.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define INPUT_BUFFER 128
#define PAGE_COUNT_BUFFER 8

static char page_count[PAGE_COUNT_BUFFER];

#include "command_line.hpp"

int main(int argc, char * argv[])
{	
	init();
	command_logic(argc, argv);
	
	return 0;
}
