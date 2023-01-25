#ifndef OBJECT_PHYE
#define OBJECT_PHYE

#include "modules/modules.h"

typedef union __object
{
    PARTICLE part;
    POLYGON poly;
    SURFACE surf;
} __OBJECT;

typedef struct object
{
    __OBJECT obj;
    OBJ_IDS id;
} OBJECT;

#endif