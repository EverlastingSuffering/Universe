#ifndef RUBBER_PARTS_PHYE
#define RUBBER_PARTS_PHYE

#include "universe.h"
#include "rules/checks/rubber_parts.h"
#include "rules/actions/rubber_parts.h"

#define RUBBER_PARTS_RULE

#ifdef OPENCL_ACCELERATION
#define RUBBER_PARTS_RULE_KERNEL_NAME "rubber_parts_rule"
#endif

void rubber_parts_rule(UNIVERSE* uni, long i);

#endif