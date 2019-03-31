#include <stdio.h>

#include "csvparser.h"

int main() {
    int i =  0;
    //                                   file, delimiter, first_line_is_header?
    CsvParser *csvparser = CsvParser_new("fish.csv", ",", 0);
    CsvRow *row;
    const CsvRow *header = CsvParser_getHeader(csvparser);
    const char **headerFields = CsvParser_getFields(header);

    if (header == NULL) {
        printf("%s\n", CsvParser_getErrorMessage(csvparser));
        return 1;
    }
    for (i = 0 ; i < CsvParser_getNumFields(header) ; i++) {
        printf("TITLE: %s\n", headerFields[i]);
    }
	//row = CsvParser_getRow(csvparser);

    while ((row = CsvParser_getRow(csvparser)) ) 
	{
        const char **rowFields = CsvParser_getFields(row);
    	printf("==NEW LINE==\n");

        for (i = 0 ; i < CsvParser_getNumFields(row) ; i++) {
            printf("FIELD: %s\n", rowFields[i]);
        }
		printf("\n");
        CsvParser_destroy_row(row);

		csvparser->header_ = NULL;
    }
    CsvParser_destroy(csvparser);
	
	getchar();
    return 0;
}
