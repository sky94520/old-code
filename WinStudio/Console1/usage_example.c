#include <stdio.h>
#include<time.h>

#include "csvparser.h"

int main() 
{
    int i =  0;
	time_t startTicks = time(NULL);
    //                                   file, delimiter, first_line_is_header?
    CsvParser *csvparser = CsvParser_new("fish.csv", ",", 0);
    CsvRow *row;

    while ((row = CsvParser_getRow(csvparser)) ) 
	{
		const char **rowFields = CsvParser_getFields(row);

    	printf("==NEW LINE==\n");

        for (i = 0 ; i < CsvParser_getNumFields(row) ; i++) 
		{
            printf("FIELD: %s\n", rowFields[i]);
        }
		printf("\n");
        CsvParser_destroy_row(row);

		//csvparser->csvStringIter_ = 0;
    }
    CsvParser_destroy(csvparser);
	

	printf("\n%d",time(NULL) - startTicks);
	getchar();

    return 0;
}