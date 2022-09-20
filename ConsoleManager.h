#ifndef CONSOLE_MANAGER_H_
#define CONSOLE_MANAGER_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define CONSOLE_MANAGER_INPUT_MAX (50)
#define CONSOLE_MANAGER_OUTPUT_MAX (50)

void ConsoleManager_init (void);
void ConsoleManager_main (void);

#endif /*CONSOLE_MANAGER_H_ */
