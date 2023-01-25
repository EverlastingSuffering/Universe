#include "simulate/simulate.h"

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

cl_command_queue createCommandQueue(cl_context context)
{
    cl_int err_num;
    cl_uint numDevices;

    if((err_num = clGetContextInfo(context,CL_CONTEXT_NUM_DEVICES,sizeof(cl_uint),&numDevices,NULL)) != CL_SUCCESS)
    {
        fprintf(stderr,"Failed fetching number of available devices\n");
        exit(err_num);
    }
    int device_buff_size = sizeof(cl_device_id)*numDevices;
    cl_device_id* devices_list = (cl_device_id*)malloc(device_buff_size);
    if((err_num = clGetContextInfo(context,CL_CONTEXT_DEVICES,device_buff_size,devices_list,NULL)) != CL_SUCCESS)
    {
        fprintf(stderr,"Failed fetching list of available devices\n");
        exit(err_num);
    }
    printAvailableDevices(devices_list,numDevices);
    printf("Choose preferable device: ");
    int device_id;
    scanf("%d",&device_id);
    if(device_id < 0 || device_id >= numDevices)
    {
        fprintf(stderr,"Invalid device index\n");
        exit(1);
    }
    cl_command_queue queue = clCreateCommandQueueWithProperties(context,devices_list[device_id],NULL,&err_num);
    if(err_num)
    {
        fprintf(stderr,"Failed creating command queue\n");
        exit(err_num);
    }
    free(devices_list);

    return queue;
}