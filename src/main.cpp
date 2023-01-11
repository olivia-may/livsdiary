/* LIVSDiary
 * (C) 2022 Olivia May GPLv3+ 
 * Contact me: olmay@tuta.io
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

#include "command_line.hpp"

/*
#include "filesystem.h"
#include "page.hpp"
#include "command_line.hpp"
*/

int main(int argc, char *argv[])
{
	check_dirs_and_files(); 
	command_logic(argc, argv);
	
	//decrement_page_count();
	//increment_page_count();
	
	//make_new_page();
	//remove_most_recent_page();

	return 0;
}
