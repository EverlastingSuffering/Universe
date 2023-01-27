#include "utils/opencl/print_info.h"
#include "universe.h"
#include <stdio.h>

void printAvailableDevices(const cl_device_id* devices, cl_uint numDevices)
{
    cl_int err_num;
    printf("======== BEGIN DEVICES LIST ========\n\n");
    for(int i = 0; i < numDevices; ++i)
    {
        printf("ID: %d\n",i);

        cl_device_type type;
        if((err_num = clGetDeviceInfo(devices[i],CL_DEVICE_TYPE,sizeof(cl_device_type),&type,NULL)) != CL_SUCCESS)
        {
            fprintf(stderr,"Can't fetch OpenCL devices info\n");
            exit(err_num);
        }
        printf("TYPE: ");
        switch(type)
        {
            case CL_DEVICE_TYPE_GPU:
                printf("GPU\n");
                break;
            case CL_DEVICE_TYPE_CPU:
                printf("CPU\n");
                break;
            case CL_DEVICE_TYPE_ACCELERATOR:
                printf("ACCELERATOR\n");
                break;
        }

        size_t size;
        if((err_num = clGetDeviceInfo(devices[i],CL_DEVICE_VENDOR,NULL,NULL,&size)) != CL_SUCCESS)
        {
            fprintf(stderr,"Can't fetch OpenCL devices info\n");
            exit(err_num);
        }
        char* vendor = (char*)malloc(size);
        if((err_num = clGetDeviceInfo(devices[i],CL_DEVICE_VENDOR,size,vendor,NULL)) != CL_SUCCESS)
        {
            fprintf(stderr,"Can't fetch OpenCL devices info\n");
            exit(err_num);
        }
        printf("VENDOR: %s\n",vendor);
        free(vendor);

        #if defined(DEVICES_INFO_MEDIUM) || defined(DEVICES_INFO_HUGE)
        cl_uint vendor_id;
        if((err_num = clGetDeviceInfo(devices[i],CL_DEVICE_VENDOR_ID,sizeof(cl_uint),&vendor_id,NULL)) != CL_SUCCESS)
        {
            fprintf(stderr,"Can't fetch OpenCL devices info\n");
            exit(err_num);
        }
        printf("VENDOR ID: %u\n",vendor_id);

        if((err_num = clGetDeviceInfo(devices[i],CL_DEVICE_VERSION,NULL,NULL,&size)) != CL_SUCCESS)
        {
            fprintf(stderr,"Can't fetch OpenCL devices info\n");
            exit(err_num);
        }
        char* device_version = (char*)malloc(size);
        if((err_num = clGetDeviceInfo(devices[i],CL_DEVICE_VERSION,size,device_version,NULL)) != CL_SUCCESS)
        {
            fprintf(stderr,"Can't fetch OpenCL devices info\n");
            exit(err_num);
        }
        printf("DEVICE OCL VERSION: %s\n",device_version);
        free(device_version);
        #endif
        #ifdef DEVICES_INFO_HUGE
        cl_uint max_compute_units;
        if((err_num = clGetDeviceInfo(devices[i],CL_DEVICE_MAX_COMPUTE_UNITS,sizeof(cl_uint),&max_compute_units,NULL)) != CL_SUCCESS)
        {
            fprintf(stderr,"Can't fetch OpenCL devices info\n");
            exit(err_num);
        }
        printf("MAX COMPUTE UNITS: %u\n",max_compute_units);

        cl_uint max_work_dim;
        if((err_num = clGetDeviceInfo(devices[i],CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,sizeof(cl_uint),&max_work_dim,NULL)) != CL_SUCCESS)
        {
            fprintf(stderr,"Can't fetch OpenCL devices info\n");
            exit(err_num);
        }
        printf("MAX WORK-ITEM DIMENSIONS: %u\n",max_work_dim);

        int sizes_buff_size = sizeof(size_t)*max_work_dim;
        size_t* max_work_sizes = (size_t*)malloc(sizes_buff_size);
        if((err_num = clGetDeviceInfo(devices[i],CL_DEVICE_MAX_WORK_ITEM_SIZES,sizes_buff_size,max_work_sizes,NULL)) != CL_SUCCESS)
        {
            fprintf(stderr,"Can't fetch OpenCL devices info\n");
            exit(err_num);
        }
        printf("MAX WORK-ITEM SIZES: (");
        for(int i = 0; i < max_work_dim; ++i)
            printf("%lu,",max_work_sizes[i]);
        printf(")\n");
        free(max_work_sizes);

        size_t max_work_group;
        if((err_num = clGetDeviceInfo(devices[i],CL_DEVICE_MAX_WORK_GROUP_SIZE,sizeof(size_t),&max_work_group,NULL)) != CL_SUCCESS)
        {
            fprintf(stderr,"Can't fetch OpenCL devices info\n");
            exit(err_num);
        }
        printf("MAX WORK-GROUP SIZE: %lu\n",max_work_group);
        #endif
        printf("\n+-\n\n");
    }
    printf("\n======== END DEVICES LIST ========\n");
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