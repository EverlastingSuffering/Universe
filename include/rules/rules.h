#include "rules/rubber_parts.h"

#ifdef OPENCL_ACCELERATION
#define RULES_KERNEL_NAMES_LIST {       \
        RUBBER_PARTS_RULE_KERNEL_NAME   \
        }
#endif

#define run_rules(uni,i)  \
        rubber_parts_rule(uni,i);