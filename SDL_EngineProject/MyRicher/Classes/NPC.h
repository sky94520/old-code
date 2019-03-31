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
	//�Ƿ�Ͷ�Ӧ���η�����ײ
	bool intersectRect(const Rect& rect);
};
#endif