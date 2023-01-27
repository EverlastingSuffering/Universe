#include "simulate/simulate.h"

void simulate_cpu(UNIVERSE* uni)
{
    for(long i = 0; i < uni->objects_num; ++i)
    {
        run_rules_cpu(uni,i)
    }
}

void simulate(UNIVERSE* uni)
{
    #ifndef OPENCL_ACCELERATION
    simulate_cpu(uni);
    #else

    cl_context context = createContext();
    cl_device_id device;
    cl_command_queue queue = createCommandQueue(context,&device);
    cl_program* programs = CreatePrograms(context,device);

    #endif
}

int main()
{
    UNIVERSE uni;
    simulate(&uni);

    return 0;
}