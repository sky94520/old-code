/*B2Entity b2Body Entity B��Ҫ��Ϊ�˺�box2d��ԭ�����������*/
#ifndef __B2Entity_H__
#define __B2Entity_H__
#include "Entity.h"
#include "Box2D/Box2D.h"

class B2Entity:public Entity
{
	/*�Ƿ��Ѿ�������ײ����֤һ֡��ֻ����ײһ��*/
	SDL_BOOL_SYNTHESIZE(m_bCollided,Collided);
protected:
	b2Body*m_pBody;
	bool m_bActive;//�Ƿ������������box2d��ײ���
public:
	B2Entity();
	~B2Entity();
	/**��ʼ������
	*/
	void initBody();
	/**Ϊ�ڲ���body���b2Fixture,�ڲ���GB2ShapeCache-x�ṩ֧��
	@shape ��GB2ShapeCache�� ��shape����Ӧ�����������
	shape��������֮ǰ�Ѿ����ص�GB2ShapeCache�У�����body����Ϊnullptr
	*/
	void addFixturesToBody(const std::string &shape);
	//���ԭ��body��ȫ��fixture
	void clearFixtures();
	//��ȡ��ǰ��״
	b2Fixture*getFixtureList()const;

	void setActive(bool active);
	bool isActive()const;
};
#endif