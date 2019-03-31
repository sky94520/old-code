#ifndef __common_H__
#define __common_H__
#define SYNTHESIZE(varType,varName,funName)\
	protected:varType varName;\
	public:void set##funName(varType v){varName=v;}\
	public:varType get##funName()const{return varName;}
#endif
