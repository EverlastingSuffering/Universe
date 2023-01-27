#include "rules/rubber_parts.h"

void rubber_parts_rule(UNIVERSE* uni, long i)
{
    if(rubber_parts_rule_check(&uni->objects[i]))
        rubber_parts_rule_action(uni,i);
}