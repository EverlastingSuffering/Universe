#ifndef UNIVERSE_PHYE
#define UNIVERSE_PHYE

#include "./object.h"
#include "./config.h"

#ifdef __OPENCL_VERSION__
#define multi_type(type) __global type
#else
#define uni_type(type) type
#endif

typedef struct l_array
{
    long long data[MAX_LINK_NUM];
} L_ARRAY;

typedef struct universe
{
    long long objects_num;
    uni_type(OBJECT) objects[MAX_OBJECTS_NUM];
    uni_type(L_ARRAY) links[MAX_OBJECTS_NUM][MAX_LINK_NUM];
} UNIVERSE;

#define uni_for_each_linked(uni,ind)    \
                for(int i = 0; i < MAX_LINK_NUM && uni->links[ind][i]; ++i)

#define uni_init(uni)   \
            uni->objects_num = 0;

#endif