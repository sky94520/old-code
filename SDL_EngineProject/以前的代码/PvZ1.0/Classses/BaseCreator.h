#ifndef __BaseCreator_H__
#define __BaseCreator_H__
class Plant;
class BaseCreator
{
public:
	virtual ~BaseCreator(){}
	virtual Plant* createObject()const=0;
};
#endif