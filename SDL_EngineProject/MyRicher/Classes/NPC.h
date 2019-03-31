#ifndef __NPC_H__
#define __NPC_H__
#include "Entity.h"
#include "ScriptEvent.h"

class NPC : public ScriptEvent,public Entity
{
public:
	NPC();
	~NPC();
	CREATE_FUNC(NPC);
	static NPC* create(const ValueMap& object);
	
	bool init();
	bool init(const ValueMap& object);
public:
	//是否和对应矩形发生碰撞
	bool intersectRect(const Rect& rect);
};
#endif