/*
scanner.c
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include "scanner.h"
#include "token.h"



int check_keyword (char string[])
{
	char * keywords [] = {"start", "stop", "loop", "void", "var", "return", "scan", "out", "program", "if", "then", "let"};
	int len = sizeof(keywords)/sizeof(keywords[0]);
	int i;

	for (i = 0; i < len; i++)
	{
		int result = strcmp(keywords[i], string);
		if (result == 0)
		{
			/* matches */
			return 1;
		}
	}
	return -1;
}

int check_operator (char string[])
{
	int i;
	char *match;
	
	char operator_array[20] =
	{
        ':',
	'+',
	'-'
	};

	for (i = 0; i < 3; i++)
        {
		match = strchr(string, operator_array[i]);
		if (match != NULL)
		{
			/*matches*/
			return 1;
		}	
	}

	return -1;
}



int check_identifier (char string[])
{
	regex_t regex;
	int status = regcomp(&regex, "^[a-z][a-zA-Z0-9_]*",0);
	status = regexec(&regex, string, 0, NULL, 0);
	if (status == 0)
	{
		regfree(&regex);
		return 1;
	}
	regfree(&regex);
	return -1;
}



int check_integer(char string[])
{
	float num = atof(string);
        if (num == 0 && string[0] != '0')
        {
                return -1;
        }
        else
	{
                float diff = num - (int)num;
                if ((diff) == 0)
                {
                        return 1;
                }
                else
                {
                        /*not integer Decimal Found*/
                        /*fprintf(stderr, "Scanner Error: Decimal Point in Integer not Valid");*/
              		
		}
        }
	return -1;
}
/*
int check_integer(char string[])
{
        regex_t regex;
        int status = regcomp(&regex, "^[0-9]+",0);
        status = regexec(&regex, string, 0, NULL, 0);
        if (status == 0)
        {
                regfree(&regex);
                return 1;
        }
        regfree(&regex);
        return -1;
}
*/



Token scanner(char tk_word[10], int line)
{
        fprintf(stderr, "\n** SCANNING **\n");
	
	Token tk;

	/*default values*/
	tk.line = line;
	tk.tkString = "test";
	tk.tkID = "nothing";
	

	fprintf(stderr,"keyword: %s\n",tk_word);
	
	if(check_keyword(tk_word) > 0)
	{
		fprintf(stderr, "MATCHED Keyword\n");		
		tk.line = line;
		tk.tkString = tk_word;
		tk.tkID = "Keyword";
		return tk;
	}
	else if (check_identifier(tk_word) > 0)
	{
		fprintf(stderr, "MATCHED Identifier\n");
                tk.line = line;
                tk.tkString = tk_word;
                tk.tkID = "Identifier";
                return tk;
	}
	else if (check_integer(tk_word) > 0)
	{
		fprintf(stderr, "MATCHED Integer\n");
                tk.line = line;
                tk.tkString = tk_word;
                tk.tkID = "Integer";
                return tk;
	}
        else if (check_operator(tk_word) > 0)
        {
                fprintf(stderr, "MATCHED Operator\n");
                tk.line = line;
                tk.tkString = tk_word;
                tk.tkID = "Operator";
                return tk;
        }

	return tk;	
}

