//PROGRAM-ID. Sorting
//AUTHOR.  Joel Perkins.
//DATE-WRITTEN. May 12, 2008.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headL4.h"

void csort(FILE* outFile, struct empRec r[], int a);
void dsort(FILE* outFile, struct empRec s[], int a);

int main()
{
	//File Pointers.
	FILE *outFile, *inFile;
    int max = 30;
    int a = 0;
    int k = 0;

	//File Variables
	char fileInName[26];
	char fileOutName[26];

	char resp;

    //raw data unsorted and untouched for multipile passes.
    struct empRec rawData[ max ];
    //copy of raw data that will be sorted.
    struct empRec r[ max ];


	//Open Input File
	printf("Enter input file name [25 Char Max]: ");
	scanf( "%s", fileInName);
	inFile = fopen( fileInName , "r" );
	if( inFile == NULL )
	{
		printf("Cannot open inFile %s.\n", fileInName);
		exit(1);
	}

	//Output File Name & check for existing name.
	printf("Enter output file name [25 Char Max]: ");
	scanf( "%s", fileOutName );
	if((outFile = fopen(fileOutName, "r" )) != NULL )
	{
		printf("\nA file by the name %s exists.\n", fileOutName);
		printf("Do you wish to overwrite (Y or N): ");
		resp = getchar();
		if((resp == 'n') || (resp == 'N'))
		{
			printf("\nProgram aborted to prevent overwrite!\n");
			exit(1);
		}
	}

	//Open Output File
	outFile = fopen(fileOutName, "w" );
	if( outFile == NULL )
	{
		printf("Cannot open outFile %s.", fileInName);
		exit(1);
	}

    //Scans in raw data and puts them in variables.
    while(fscanf(inFile,"%s",&rawData[a].sur) != EOF)
    {
            fscanf(inFile,"%s%s%f%s", &rawData[a].given, &rawData[a].dep, &rawData[a].rate, &rawData[a].eye);
            a++;
    }

    //Loop that copys all raw data into another array.
    while(k <= a)
    {
            r[k] = rawData[k];
            k++;
    }

    k = 0;//reinitialize k for reuse in loop.
    //Prints unsorted raw data.
    fprintf(outFile, "\n\t\t\t%s%d\n", "Raw unsorted data:", a);
    while(k < a)
    {
        fprintf(outFile,"%21s%21s%21s%10.2f%11s\n", rawData[k].sur, rawData[k].given, rawData[k].dep,
        rawData[k].rate, rawData[k].eye);
        k++;
    }

    //Prints Sorted data.
    dSort(outFile, r, a);
    cSort(outFile, rawData, a);

    //Closing opened files.
    fclose(inFile);
    fclose(outFile);
    return 0;
}
