#ifndef PARTICLE_PHYE
#define PARTICLE_PHYE

typedef enum part_type
{
    PT_REGULAR,
    PT_RUBBER,
    PT_WATER,
    __PT_LAST
} PART_TYPE;

typedef struct particle
{
    PART_TYPE type;
    long long id;
    float x,y,z;
    float vx,vy,vz;
} PARTICLE;

#endif