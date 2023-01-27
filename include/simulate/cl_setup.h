#ifndef CL_DEVICES_PHYE
#define CL_DEVICES_PHYE

#include <CL/cl.h>

cl_command_queue createCommandQueue(cl_context context, cl_device_id* device);
cl_context createContext();
cl_program* CreatePrograms(cl_context context, cl_device_id device);

#endif