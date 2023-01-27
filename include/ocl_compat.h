#ifndef OCL_COMPAT_PHYE
#define OCL_COMPAT_PHYE

#ifdef __OPENCL_VERSION__
#define compat_type(type) __global type
#define local_compat_type(type) __local type
#define private_compat_type(type) __local type
#define constant_compat_type(type) __local type
#define uni_long long
#define uni_int long
#define uni_float float
#define uni_double double
#define uni_short short
#else
#include "CL/cl.h"
#define global_compat_type(type) type
#define local_compat_type(type) type
#define private_compat_type(type) type
#define constant_compat_type(type) type
#define uni_long cl_long
#define uni_int cl_long
#define uni_float cl_float
#define uni_double cl_double
#define uni_short cl_short
#endif
#define STRUCT_OCL_ATTRS __attribute__ ((packed))

#endif