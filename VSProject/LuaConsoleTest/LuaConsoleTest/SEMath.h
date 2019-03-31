#ifndef __SDL_Math_H__
#define __SDL_Math_H__
/*SDL_Engine Math*/
#include<cstdlib>
#include<cmath>

#define FLT_EPSILON 1.192092896e-07F        /* smallest such that 1.0+FLT_EPSILON != 1.0 */
#define MAX_UINT 0xffffffff
#define SDL_REPEAT_FOREVER (MAX_UINT - 1)
#define MAX(x,y) ((x)>(y)?(x):(y))
#define MIN(x,y) ((x)>(y)?(y):(x))
#define RANDOM(start,end) (fmodf(rand(),(end)-(start))+(start))/*[start,end) 不需要自己手动调用srand，已经在Director中调用*/
#define RANDOM_0_1() ((float)rand()/RAND_MAX)

#endif