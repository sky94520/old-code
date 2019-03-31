/*B2Entity b2Body Entity B主要是为了和box2d的原有类进行区分*/
#ifndef __B2Entity_H__
#define __B2Entity_H__
#include "Entity.h"
#include "Box2D/Box2D.h"

class B2Entity:public Entity
{
	/*是否已经发生碰撞，保证一帧，只是碰撞一次*/
	SDL_BOOL_SYNTHESIZE(m_bCollided,Collided);
protected:
	b2Body*m_pBody;
	bool m_bActive;//是否存活，如果是则存在box2d碰撞面积
public:
	B2Entity();
	~B2Entity();
	/**初始化刚体
	*/
	void initBody();
	/**为内部的body添加b2Fixture,内部由GB2ShapeCache-x提供支持
	@shape 在GB2ShapeCache中 的shape所对应的形体的名称
	shape必须在这之前已经加载到GB2ShapeCache中，并且body不能为nullptr
	*/
	void addFixturesToBody(const std::string &shape);
	//清除原来body的全部fixture
	void clearFixtures();
	//获取当前形状
	b2Fixture*getFixtureList()const;

	void setActive(bool active);
	bool isActive()const;
};
#endif