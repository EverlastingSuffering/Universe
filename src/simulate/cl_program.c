#include "simulate/simulate.h"

cl_program* CreatePrograms(cl_context context, cl_device_id device)
{
    cl_program* programs = (cl_program*)malloc(sizeof(cl_program)*OCL_SOURCES_NUM);
    const char* ocl_sources_list[] = OCL_SOURCE_FILES_LIST;
    for(int i = 0; i < OCL_SOURCES_NUM; ++i)
    {
        cl_int err_num;
        char source_name[100] = OCL_SOURCES_DIR;
        strcat(source_name,ocl_sources_list[i]);
        FILE* source = fopen(source_name,"r");
        if(source == NULL)
        {
            printf("Failed to open kernel source file '%s'\n",source_name);
            exit(1);
        }
        fseek(source,0,SEEK_END);
        long source_size = ftell(source);
        fseek(source,0,SEEK_SET);
        char* source_str = (char*)malloc(source_size);
        fread(source_str,sizeof(char),source_size,source);
        fclose(source);
        cl_program program = clCreateProgramWithSource(context,1,(const char**)&source_str,NULL,&err_num);
        if(err_num)
        {
            fprintf(stderr,"Failed to create CL program from source\n");
            exit(err_num);
        }
        err_num = clBuildProgram(program,1,&device,"-I ../include/",NULL,NULL);
        if(err_num != CL_SUCCESS)
        {
            printf("%d",err_num);
            char build_log[16384];
            clGetProgramBuildInfo(program,device,CL_PROGRAM_BUILD_LOG,sizeof(build_log),build_log,NULL);
            FILE* flog = fopen("cl_build.log","w");
            fputs(build_log,flog);
            fprintf(stderr,"Failed to build CL program from source. See 'cl_build.log' for more information\n");
            clReleaseProgram(program);
            fclose(flog);
            exit(err_num);
        }
        programs[i] = program;
    }

    return programs;
}