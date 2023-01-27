#include "simulate/simulate.h"
#include "utils/opencl/print_info.h"

cl_context createContext()
{
    cl_int err_num;
    cl_uint numPlatforms;

    if((err_num = clGetPlatformIDs(0,NULL,&numPlatforms)) != CL_SUCCESS)
    {
        fprintf(stderr,"Can't fetch number of OpenCL platforms\n");
        exit(err_num);
    }
    if(!numPlatforms)
    {
        fprintf(stderr,"There are no platforms available. Do you have OpenCL installed?\n");
        exit(1);
    }
    cl_platform_id* platforms_list = (cl_platform_id*)malloc(sizeof(cl_platform_id)*numPlatforms);
    if((err_num = clGetPlatformIDs(numPlatforms,platforms_list,NULL)) != CL_SUCCESS)
    {
        fprintf(stderr,"Can't fetch OpenCL platforms list\n");
        exit(err_num);
    }
    printAvailableProfiles(platforms_list,numPlatforms);
    printf("Choose preferable profile: ");
    int platform_id;
    scanf("%d",&platform_id);
    if(platform_id < 0 || platform_id >= numPlatforms)
    {
        fprintf(stderr,"Invalid platform index\n");
        exit(1);
    }
    cl_context_properties context_props[] = { CL_CONTEXT_PLATFORM, platforms_list[platform_id] };
    cl_context context = clCreateContextFromType(context_props,CL_DEVICE_TYPE_GPU,NULL,NULL,&err_num);
    if(err_num != CL_SUCCESS)
    {
        fprintf(stderr,"Failed creating context\n");
        exit(1);
    }
    free(platforms_list);

    return context;
}