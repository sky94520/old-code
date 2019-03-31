#ifndef __Entity_H__
#define __Entity_H__
#include "cocos2d.h"
USING_NS_CC;
class Entity : public Node
{
public:
	virtual bool init();
	Entity();
	~Entity();

	void bindSprite(Sprite*sprite);
	void run(Action*act);

	int getHitPoints();
	void setHitPoints(int HP);

	std::string getID();
	void setID(std::string str);
//¼ì²âÅö×²
	virtual bool isCollided(Entity*entity);
protected:
	Sprite*m_sprite;
	//HP
	int m_hitPoints;

	std::string m_id;
};
#endif