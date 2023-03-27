#include "main.h"

int main(){
	printf("Hello, World!\n");

	{
		char char_var = input();
		printf("I got '%c' for return value\n", char_var);
	}

	test();

	return 0;
}

