/*
Shaon Islam
main.c
*/




#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"
#include "node.h"

int main(int argc,char* argv[])
{
	if (argc > 2)
	{
		printf("Error: Too many arguments\n");
		return 0;
	}

	if (argc == 2)
	{	
		/*___ Open File___ */
		char *fp;
		fp = malloc(strlen(argv[1] + 7));
		strcpy (fp, argv[1]);
		strcat(fp, ".fs182");
		
		FILE *file1;
		file1 = fopen(fp, "r");
		if (file1 == NULL)
		{
			perror("Fail to open: ");
			return 1;
		} 

		/*__read file__		
		if(!feof(file1)){
			parser(file1);
		}*/


		char tk_array[20][10];
		int line_array[20];

		int i = 0;
		int line_number = 0;
		char delimit[]=" \t\r\n\v\f";

		char line[60];	
		char *p = NULL;
		char pp[100];
		while (fgets(line, 20, file1) != NULL)	
		{
			line_number++;
			p = strtok(line, delimit);
			while(p != NULL)
			{
				fprintf(stderr, "Line #%d: %s\n", line_number, p); 
				strcpy(tk_array[i], p);
				line_array[i] = line_number;
				strcpy(pp, p);
				p = strtok(NULL, delimit);		
				i++;
				
			}
		}

		parser(tk_array, line_array);
		fclose(file1);
	}

	return 0;
}

