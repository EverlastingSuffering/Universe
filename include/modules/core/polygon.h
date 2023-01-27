#ifndef POLYGON_PHYE
#define POLYGON_PHYE

#include "modules/core/particle.h"
#include "ocl_compat.h"

typedef struct STRUCT_OCL_ATTRS polygon
{
    uni_long id;
    PARTICLE a,b,c;
} POLYGON;

#endif