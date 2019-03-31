#ifndef __Platform_H__
#define __Platform_H__
#include<cstdio>
#define SDL_SAFE_DELETE(p)do{if(p) delete p;p=nullptr;}while(0)
//自定义宏 主要用于简化开发
#define SDL_SYNTHESIZE(varType,varName,funName)\
protected:varType varName;\
public:virtual varType get##funName()const{return varName;}\
public:virtual void set##funName(const varType& var) {varName = var;}

#define SDL_BOOL_SYNTHESIZE(varName,funName)\
protected:bool varName;\
public:virtual bool is##funName()const{return varName;}\
public:virtual void set##funName(bool var){varName = var;}
#endif