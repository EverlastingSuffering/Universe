#include "simulate/simulate.h"
#include "utils/opencl/print_info.h"

cl_command_queue createCommandQueue(cl_context context, cl_device_id* device)
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
    *device = devices_list[device_id];
    cl_command_queue queue = clCreateCommandQueueWithProperties(context,*device,NULL,&err_num);
    if(err_num)
    {
        fprintf(stderr,"Failed creating command queue\n");
        exit(err_num);
    }
    free(devices_list);

    return queue;
}