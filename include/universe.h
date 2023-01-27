#ifndef UNIVERSE_PHYE
#define UNIVERSE_PHYE

#include "object.h"
#include "config.h"
#include "ocl_compat.h"

typedef struct universe
{
    long objects_num;
    OBJECT objects[MAX_OBJECTS_NUM];
    uni_long links[MAX_OBJECTS_NUM][MAX_LINK_NUM];
} UNIVERSE;

#define uni_for_each_linked(uni,ind)    \
                for(int i = 0; i < MAX_LINK_NUM && uni->links[ind][i]; ++i)

#define uni_init(uni)   \
            uni->objects_num = 0;

#endif