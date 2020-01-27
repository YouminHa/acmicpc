#include <stdio.h>

#ifdef DEBUG
#define LOG(fmt, ...) do { printf("[LOG: %s():%d] "fmt"\n", __FUNCTION__, __LINE__, ##__VA_ARGS__); } while(0)
#else
#define LOG(fmt, ...)
#endif

#define MIN(a, b) ((a)<(b)?(a):(b))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define ABS(a) ((a)>=0?(a):-(a))
#define DIFF(a, b) ((a)<(b)?(a)-(b):(b)-(a))
