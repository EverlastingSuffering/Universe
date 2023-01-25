#ifndef UNIVERSE_PHYE
#define UNIVERSE_PHYE

#include "./utils/vector/vector.h"
#include "./object.h"
#include "./config.h"

typedef struct l_array
{
    long long data[MAX_LINK_NUM];
} L_ARRAY;

typedef struct universe
{
    cvector_vector_type(OBJECT) objects;
    cvector_vector_type(L_ARRAY) links;
} UNIVERSE;

#endif