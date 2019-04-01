#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 1024

int main()
{
	char str[MAX_LENGTH];
	char temp = '\0';
	int i = 0;
	int length = 0;

	memset(str, '\0', MAX_LENGTH * sizeof(char));
	puts("Please input an string");
	scanf("%s", str);
	//get the length
	length = strlen(str);

	for (i = 0; i < length / 2; i++)
	{
		temp = str[i];
		str[i] = str[length - i - 1];
		str[length - i - 1] = temp;
	}
	puts("revert string is");
	puts(str);

	return 0;
}
