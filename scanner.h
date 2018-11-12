#ifndef SCANNER_H
#define SCANNER_H

#include "token.h"

Token scanner(char tk_word[10], int line);





int check_keyword (char string[]);
int check_identifier (char string[]);
int check_integer(char string[]);
int check_operator(char string[]);

#endif
