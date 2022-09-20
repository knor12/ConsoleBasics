#ifndef CONSOLE_MANAGER_VAR_H_
#define CONSOLE_MANAGER_VAR_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "string.h"


  typedef enum
  {
    TYPE_U32,
    TYPE_32,
    TYPE_f32,
    TYPE_Bool,


  } ConsoleManagerDatumType_t;


  typedef struct
  {

    ConsoleManagerDatumType_t type;
    void *pData;
    char *pName;

  } ConsoleManagerDatum_t;



  uint32_t var1, var2, var3, var4;

  extern ConsoleManagerDatum_t variable[]; 
  extern const uint32_t NUM_VARS; 

#endif /*CONSOLE_MANAGER_VAR_H_ */