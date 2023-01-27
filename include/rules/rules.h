#include "rules/rubber_parts.h"

#ifdef OPENCL_ACCELERATION
#define RULES_KERNEL_NAMES_LIST {       \
        RUBBER_PARTS_RULE_KERNEL_NAME   \
        }

#define KERNELS_NUM (sizeof((char*[])RULES_KERNEL_NAMES_LIST) / sizeof(char*))
#define OCL_SOURCES_DIR "../src/rules/ocl/"
#define OCL_SOURCE_FILES_LIST {                     \
                            "rubber_parts.ocl"      \
                            }
#define OCL_SOURCES_NUM (sizeof((char*[])OCL_SOURCE_FILES_LIST) / sizeof(char*))
#endif

#define run_rules_cpu(uni,i)  \
        rubber_parts_rule(uni,i);