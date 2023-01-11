/* (C) 2022 Olivia May GPLv3+ */ 

#include <math.h>
#include <string.h>

#define NUMBER_BUFFER 8

// i tried, and it feels weird doing this, but i cant find anything for this, so i dont know what else to do
char * convert_to_char_array(int number) 
{
	static char array[NUMBER_BUFFER];	
	
	if (number == 0)
	{
		array[0] = '0';
		array[1] = 0;
		return array;
	}
	
	char storage[NUMBER_BUFFER];
	int i = 0;
	int j;

	while (true)
	{
		if (number == 0) { break; }

		if (number % 10 == 0) { storage[i] = '0'; }
		if (number % 10 == 1) { storage[i] = '1'; }
		if (number % 10 == 2) { storage[i] = '2'; }
		if (number % 10 == 3) { storage[i] = '3'; }
		if (number % 10 == 4) { storage[i] = '4'; }
		if (number % 10 == 5) { storage[i] = '5'; }
		if (number % 10 == 6) { storage[i] = '6'; }
		if (number % 10 == 7) { storage[i] = '7'; }
		if (number % 10 == 8) { storage[i] = '8'; }
		if (number % 10 == 9) { storage[i] = '9'; }
		
		number = number / 10;
		
		i++;
	}
	
	for (j = 0; j < i; j++)
	{
		array[j] = storage[i - j - 1];

	}
	array[i] = 0;

	return array;
}

// warning: will break for long numbers (int digit_slot overflows), like '12343678912'
int convert_to_int(char *str)
{
	int i;
	int number = 0;
	int len = strlen(str);
	for (i = 0; i < len; i++)
	{
		int digit_slot = pow(10, len - i - 1);

		if (str[i] == '0') { number = number + 0 * digit_slot; }
		if (str[i] == '1') { number = number + 1 * digit_slot; }
		if (str[i] == '2') { number = number + 2 * digit_slot; }
		if (str[i] == '3') { number = number + 3 * digit_slot; }
		if (str[i] == '4') { number = number + 4 * digit_slot; }
		if (str[i] == '5') { number = number + 5 * digit_slot; }
		if (str[i] == '6') { number = number + 6 * digit_slot; }
		if (str[i] == '7') { number = number + 7 * digit_slot; }
		if (str[i] == '8') { number = number + 8 * digit_slot; }
		if (str[i] == '9') { number = number + 9 * digit_slot; }
	}

	return number;
}
