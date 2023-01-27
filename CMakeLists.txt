cmake_minimum_required(VERSION 3.0)
project(UNI)
add_compile_options(-Wall -O3)
add_executable(UNI
                src/simulate/simulate.c
                src/simulate/cl_context.c
                src/simulate/cl_comand_queue.c
                src/simulate/cl_program.c
                src/utils/opencl/print_info.c
                src/universe.c
                src/rules/cpu/rubber_parts.c
            )
find_package(OpenCL REQUIRED)
target_link_libraries(UNI OpenCL::OpenCL)
target_include_directories(UNI PUBLIC "${PROJECT_SOURCE_DIR}/include")