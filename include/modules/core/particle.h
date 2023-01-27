#ifndef PARTICLE_PHYE
#define PARTICLE_PHYE

#include "ocl_compat.h"

typedef enum part_type
{
    PT_REGULAR,
    PT_RUBBER,
    PT_WATER,
    __PT_LAST
} PART_TYPE;

typedef struct STRUCT_OCL_ATTRS particle
{
    PART_TYPE type;
    uni_long id;
    uni_float x,y,z;
    uni_float vx,vy,vz;
} PARTICLE;

#endif