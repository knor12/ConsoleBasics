#include "ConsoleManager.h"
#include "string.h"
#include "ConsoleManagerGlue.h"
#include "ConsoleManagerVar.h"
#include <string.h>


#define NO_TOKEN (0)

int myAtoi(char* str)
{
    // Initialize result
    int res = 0;

    for (int i = 0; str[i] != '\0'; ++i)
        res = res * 10 + str[i] - '0';
 
    // return result.
    return res;
}

/*function compares two null terminated strings
* return true if match, return false otherwise.
*/
static bool
my_strcmp (char *str1, char *str2)
{
  uint32_t length = strlen (str1);
  if (length > strlen (str2))
    {
     length = strlen (str2);
    }

  uint32_t i; 
  for (i = 0; i < length; i++)
     {

      if ((char) (*(str1 + i)) != (char) (*(str2 + i)))
	{
	  return false;
	}
	
}
  return true;



}






/*reads a '\n' or '\r' terminated string from standard input
*return true of a string is received, otherwise return 0
*/
static bool
isStringReceived (char *str, uint32_t * strSize)
{

  static char in[CONSOLE_MANAGER_INPUT_MAX] = { 0 };
  /*static*/ uint32_t inSize = 0;


  char c;
  bool isChar = getCharacter (&c);

  /*read characters untill no characters to read */
  while (isChar == true)
    {

      in[inSize] = c;
      inSize++;
      isChar = getCharacter (&c);

      /*if reached end of line */
      if (c == '\n' || c == '\r')
	{
	  /*copy string to destination */
	  memcpy (str, in, inSize);

	  /*copy the size of the string received */
	  *strSize = inSize;

	  /*clear the buffer for the next sting */
	  memset (in, 0, CONSOLE_MANAGER_INPUT_MAX);
	  inSize = 0;

	  /*full string received */
	  return true;

	}

    }

  /*partial string or no string received */
  return false;
}


/*true if a token is found, otherwise return NO_TOKEN=0*/
char *
getToken (char *in, uint32_t tokenOrderNumber)
{

  char *str = in;
  uint32_t index = 0;
  uint32_t tokenCounter = 0;

  while (index < CONSOLE_MANAGER_INPUT_MAX - 1 && (*str) != 0 && (*str) != '\n'
	 && (*str) != '\r')
    {
      index++;
      if (tokenOrderNumber == tokenCounter)
	{
	  //printf("%s \n", str);
	  return str;
	}

      str++;


      /*see if we hit another token */
      if (*str == ' ')
	{
	  tokenCounter++;

	  /*only consider one white space, ignore the others */
	  while (*str == ' ')
	    {
	      str++;
	    }
	}

    }



  return NO_TOKEN;

}

/*return true if the input string is a numeric*/
bool
isNumeric (char *token)
{

  char *str = token;

  bool isN = true;


  do
    {

      if (*str > '9' || *str < '0')
	    {
	     isN = false;
	     //printf ("%s fun not numeric \n", str);
	    }
         else
	    {
	     //printf ("%s fun is numeric \n", str);
	    }
      str++;
      
      if(*str == ' ')
      {
         break;  
      }
      
    }while ((*str != '\t') &&(*str != ' ') && (*str != '\n') && (*str != '\r') && (*str != 0));

  return isN;

  }


  void ConsoleManager_processTokenSet (char *in, char *out)
  {

    /*set variable_name numeric */
    int num_elements = NUM_VARS;
    
    /*check if we have enough commands for this instruction*/
    char *token = getToken (in, 2);
    if (token == NO_TOKEN)
    {
        snprintf (out, CONSOLE_MANAGER_OUTPUT_MAX,"not enough commands\n ");
        return; 
    }
    
    /*get variable name*/
    token = getToken (in, 1);
    for (int i = 0; i < num_elements; i++)
      {
	if (my_strcmp (token, variable[i].pName))
	  {
	    if (variable[i].type == TYPE_U32)
	      {

		/*check if token 3 is numeric this is the value to be written*/
		token = getToken (in, 2);
		if (!isNumeric (token))
		  {
		    snprintf (out, CONSOLE_MANAGER_OUTPUT_MAX,
			      "%s is not numeric\n", token);
		    return;
		  }

		uint32_t *data = (uint32_t *) variable[i].pData;

		*data = myAtoi (token);
		snprintf (out, CONSOLE_MANAGER_OUTPUT_MAX, "ok \n");
		return;


	      }
	    else
	      {
		snprintf (out, CONSOLE_MANAGER_OUTPUT_MAX,
			  "%d type not supported by parser\n ",
			  variable[i].type);
		return;
	      }


	  }
      }


    snprintf (out, CONSOLE_MANAGER_OUTPUT_MAX, "%s variable not found\n",
	      getToken (in, 1));

  }


  void ConsoleManager_processTokenGet (char *in, char *out)
  {

    /*get variable_name */
        int num_elements = NUM_VARS;
    char *token = getToken (in, 1);
    
    if (token == NO_TOKEN)
    {
        snprintf (out, CONSOLE_MANAGER_OUTPUT_MAX,"not enough commands\n");
        return; 
    }

    for (int i = 0; i < num_elements; i++)
      {
      if (my_strcmp (token, variable[i].pName))
	     {
	        if (variable[i].type == TYPE_U32)
	         {
	             uint32_t * num = (uint32_t *) variable[i].pData;
	             snprintf (out, CONSOLE_MANAGER_OUTPUT_MAX,"%d\n" , *num);
			        return; 
	          }
	         else 
	         {
	          snprintf (out, CONSOLE_MANAGER_OUTPUT_MAX,"%d type not supported by parser\n",variable[i].type);
		        return;
	          
	         }
	          
	      }
	  }
          

    snprintf (out, CONSOLE_MANAGER_OUTPUT_MAX, "%s variable not found\n",
	      getToken (in, 1));
	      return; 
  }

  void ConsoleManager_main (void)
  {

    /*define variables */
    char out[CONSOLE_MANAGER_OUTPUT_MAX] = { 0 };
    char in[CONSOLE_MANAGER_INPUT_MAX] = { };
    char *token;
    uint32_t inSize = 0;

    /*check if we receifed a string */
    if (isStringReceived (in, &inSize))
      {


	{

	  token = getToken (in, 0);
	  if (token != NO_TOKEN)
	    {
	      //printf ("token%d=%s is numeric=%d \n", i, token , isNumeric(token));
	      if (my_strcmp (token, "get"))
		{
		  ConsoleManager_processTokenGet (in, out);
		  printStrig (out);

		}
	      else if (my_strcmp (token, "set"))
		{
		  ConsoleManager_processTokenSet (in, out);
		  printStrig (out);

		}
	      else
		{
		  snprintf (out, CONSOLE_MANAGER_OUTPUT_MAX,
			    "command %s not supported \n", token);
		  printStrig (out);
		}
	    }

	  //

	}
	//printf ("in %s\n", in);
	//printf("out %s\n" , out); 
      }
    else
      {

	/*nothing to do, no string received */
      }

  }
  
  /*initialization code of the ConsoleManager*/
  void ConsoleManager_init (void)
  {

    printStrig ("starting up.\n type a command...\n");

  }
