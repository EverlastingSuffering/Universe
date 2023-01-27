#ifndef CONFIG_PHYE
#define CONFIG_PHYE

#define MAX_LINK_NUM 20
#define MAX_OBJECTS_NUM 1000

#define OPENCL_ACCELERATION

#ifdef OPENCL_ACCELERATION
#define DEVICES_INFO_MEDIUM
#define DEVICES_INFO_HUGE
#endif

#ifdef __OPENCL_VERSION__
#define compat_type(type) __global type
#else
#define compat_type(type) type
#endif

#endif