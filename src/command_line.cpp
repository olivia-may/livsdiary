/* (C) 2022 Olivia May GPLv3+ */

#include "livsdiary.h"
#include "converters.h"
#include "time.h"
#include "filesystem.h"
#include "page.hpp"
#include "command_line.hpp"

int main()
{
	printf("** command_line.cpp **\n");

	char * array[2];
	array[0] = "test1";
	array[1] = "-n";
	command_logic(1, array);
	command_logic(2, array);

	invalid("test");
	no_arg();
	version();
	help();
	printf("%b\n", check_input_is_int("test"));
	printf("%b\n", check_input_is_int("1"));
	printf("%b\n", check_input_is_int("123"));
	check_input_is_int("1");

	edit("1");

	return 0;
}
