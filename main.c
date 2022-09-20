#include <stdio.h>
#include "ConsoleManager.h"

int main()
{
    ConsoleManager_init ();
    
    
    while(1)
    {
        
        ConsoleManager_main(); 
    }

    return 0;
}
