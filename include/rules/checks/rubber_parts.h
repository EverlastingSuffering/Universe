#ifndef RUBBER_PARTS_CHECK_PHYE
#define RUBBER_PARTS_CHECK_PHYE

#include "universe.h"

static inline uni_int rubber_parts_rule_check(const OBJECT* obj)
{
    return (obj->id == ID_PARTICLE) && (obj->obj.part.type == PT_RUBBER);
}

#endif