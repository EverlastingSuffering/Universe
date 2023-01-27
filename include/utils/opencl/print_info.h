#ifndef PRINT_INFO_OCL_PHYE
#define PRINT_INFO_OCL_PHYE

#include <CL/cl.h>

void printAvailableProfiles(cl_platform_id* platfroms, cl_int numPlatforms);
char* getProfileInfo(cl_platform_id id, cl_platform_info info_type);

void printAvailableDevices(const cl_device_id* devices, cl_uint numDevices);

#endif