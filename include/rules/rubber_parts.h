#ifndef RUBBER_PARTS_PHYE
#define RUBBER_PARTS_PHYE

#include "./universe.h"

#define RUBBER_PARTS_RULE

#ifdef OPENCL_ACCELERATION
#define RUBBER_PARTS_RULE_KERNEL_NAME "rubber_parts_rule"
#endif

int rubber_parts_rule_check(OBJECT obj);

void rubber_parts_rule_action(UNIVERSE* uni, long long i);

void rubber_parts_rule(UNIVERSE* uni, long long i);

#endif