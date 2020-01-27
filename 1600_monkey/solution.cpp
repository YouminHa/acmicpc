#define DEBUG 1

#include <stdio.h>
#ifdef DEBUG
#define LOG(s, __VA_ARGS__) do { printf(s"\n", __VA_ARGS__); } while(0)
#else
#define LOG(s, __VA_ARGS__)
#endif


