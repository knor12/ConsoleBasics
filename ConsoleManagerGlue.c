#include "ConsoleManagerGlue.h"

#if CONSOLE_MANAGER_UNIT_TEST == (1)
#include <stdio.h>
#endif
#define CONSOLE_MANAGER_UNIT_TEST (1)


/*glue*/

/*read a character from standard input
*
*return true if a character is read, return false if no character is available
*/

bool
getCharacter (char *c)
{

#if CONSOLE_MANAGER_UNIT_TEST == (1)
  char ch = getchar ();
  *c = ch;
  return true;

#else

#endif

}


/*
*write a string to standard out put
*/
void
printStrig (char *str)
{
#if CONSOLE_MANAGER_UNIT_TEST == (1)

  printf ("%s", str);

#else

#endif

}
/*end glue*/