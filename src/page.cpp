/* (C) 2022 Olivia May GPLv3+ */

#include "livsdiary.h"
#include "converters.h"
#include "time.h"
#include "filesystem.h"
#include "page.hpp"

int main()
{
	printf("** page.cpp **\n");

	Page test;
	test.page_num = "1";
	test.edit();
}
