#ifndef CONSOLE_MANAGER_GLUE_H_
#define CONSOLE_MANAGER_GLUE_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "string.h"



/*glue*/

/*read a character from standard input
*
*return true if a character is read, return false if no character is available
*/

bool
getCharacter (char *c);


/*
*write a string to standard out put
*/
void
printStrig (char *str);

#endif /*CONSOLE_MANAGER_GLUE_H_ */