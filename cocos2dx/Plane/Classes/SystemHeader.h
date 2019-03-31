#ifndef __SystemHeader_H__
#define __SystemHeader_H__
#include "Box2D/Box2D.h"
/*引入通用头文件，通用宏，全局变量等*/
/**/
typedef struct MyBody
{
	b2BodyType type;
	b2Vec2 position;
	float32 density;
	float32 firction;
	uint16 categoryBits;
	uint16 maskBits;
public:
	MyBody(b2BodyType type=b2_dynamicBody,b2Vec2 position=b2Vec2(0.f,0.f),float32 density=1.f,
		float32 firction=0.f,uint16 categoryBits=0x0000,uint16 maskBits=0xFFFF)
		:type(type),position(position),density(density),
		firction(firction),categoryBits(categoryBits),maskBits(maskBits){}
}MyBody;
typedef enum 
{
	kBulletType_normal,
	kBulletType_double
}BulletType;
#define MY_SYNTHESIZE_BOOL(varName, funName)\
protected: bool varName;\
public: virtual bool is##funName(void) const { return varName; }\
public: virtual void set##funName(bool var){ varName = var; }
#endif