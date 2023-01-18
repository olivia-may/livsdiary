#include <stdio.h>

#include "livsdiary.h"
#include "converters.h"

int main()
{
	convert_to_char_array(3);
	printf("%s\n", converted_int);
	convert_to_char_array(2);
	printf("%s\n", converted_int);
	convert_to_char_array(1);
	printf("%s\n", converted_int);
	convert_to_char_array(0);
	printf("%s\n", converted_int);
	convert_to_char_array(42);
	printf("%s\n", converted_int);
	convert_to_char_array(512);
	printf("%s\n", converted_int);
	convert_to_char_array(1231);
	printf("%s\n", converted_int);

	char test_string[8];
	convert_to_char_array(3);
	strcpy(test_string, converted_int);
	printf("test string = %s\n", test_string);
	convert_to_char_array(0);
	strcpy(test_string, converted_int);
	printf("test string = %s\n", test_string);
	convert_to_char_array(12);
	strcpy(test_string, converted_int);
	printf("test string = %s\n", test_string);
	convert_to_char_array(535);
	strcpy(test_string, converted_int);
	printf("test string = %s\n", test_string);
	convert_to_char_array(1235);
	strcpy(test_string, converted_int);
	printf("test string = %s\n", test_string);
	
	printf("%d\n", convert_to_int("3"));
	printf("%d\n", convert_to_int("2"));
	printf("%d\n", convert_to_int("1"));
	printf("%d\n", convert_to_int("0"));

	return 0;
}
