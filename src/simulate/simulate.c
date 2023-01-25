#include "simulate/simulate.h"

void simulate_cpu(UNIVERSE* uni)
{
    for(long long i = 0; i < cvector_size(uni->objects); ++i)
    {
        run_rules(uni,i)
    }
}

char* getProfileInfo(cl_platform_id id, cl_platform_info info_type)
{
    size_t size;
    cl_int err_num;
    if((err_num = clGetPlatformInfo(id,info_type,0,NULL,&size)) != CL_SUCCESS)
    {
        fprintf(stderr,"Can't fetch OpenCL profiles info\n");
        exit(err_num);
    }
    char* info = (char*)malloc(size);
    if((err_num = clGetPlatformInfo(id,info_type,size,info,NULL)) != CL_SUCCESS)
    {
        fprintf(stderr,"Can't fetch OpenCL profiles info\n");
        exit(err_num);
    }
    
    return info;
}

void printAvailableProfiles(cl_platform_id* platfroms, cl_int numPlatforms)
{
    cl_int err_num;
    printf("======== BEGIN PROFILES LIST ========\n\n");
    for(int i = 0; i < numPlatforms; ++i)
    {
        printf("ID: %d\n",i);
        char* info = getProfileInfo(platfroms[i],CL_PLATFORM_PROFILE);
        printf("PROFILE: %s\n",info);
        free(info);
        info = getProfileInfo(platfroms[i],CL_PLATFORM_VERSION);
        printf("VERSION: %s\n",info);
        free(info);
        info = getProfileInfo(platfroms[i],CL_PLATFORM_NAME);
        printf("NAME: %s\n",info);
        free(info);
        info = getProfileInfo(platfroms[i],CL_PLATFORM_VENDOR);
        printf("VENDOR: %s\n",info);
        free(info);
        printf("\n+-\n\n");
    }
    printf("\n======== END PROFILES LIST ========\n");
}

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

void simulate(UNIVERSE* uni)
{
    #ifndef OPENCL_ACCELERATION
    simulate_cpu(uni);
    #else

    cl_context context = createContext();
    cl_command_queue queue = createCommandQueue(context);

    #endif
}

int main()
{
    UNIVERSE uni;
    simulate(&uni);

    return 0;
}