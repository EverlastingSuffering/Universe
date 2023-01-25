#include "./rules/rubber_parts.h"

void rubber_parts_rule_action(UNIVERSE* uni, long long i)
{
    for(int j = 0; j < MAX_LINK_NUM && uni->links[i].data[j]; ++j)
    {

    }
}

int rubber_parts_rule_check(OBJECT obj)
{
    return (obj.id == ID_PARTICLE) && (obj.obj.part.type == PT_RUBBER);
}

void rubber_parts_rule(UNIVERSE* uni, long long i)
{
    if(rubber_parts_rule_check(uni->objects[i]))
        rubber_parts_rule_action(uni,i);
}