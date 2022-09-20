 #include "ConsoleManagerVar.h"
 
  uint32_t var1, var2, var3, var4;

  ConsoleManagerDatum_t variable[] = {
    {
     .type = TYPE_U32,
     .pData = (void *) (&var1),
     .pName = "var1",
     },

    {
     .type = TYPE_U32,
     .pData = (void *) (&var2),
     .pName = "var2",
     },

    {
     .type = TYPE_U32,
     .pData = (void *) (&var3),
     .pName = "var3",
     },
  };
  
  const uint32_t  NUM_VARS = (sizeof(variable)/sizeof(variable[0]));