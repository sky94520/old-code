#include "Entity.h"
#include "cmath"

bool Entity::init()
{
	return true;
}
Entity::Entity()
{
	m_sprite = NULL;
	m_hitPoints = 0;
}
Entity::~Entity()
{

}
void Entity::bindSprite(Sprite*sprite)
{
	m_sprite = sprite;
	this->addChild(m_sprite);

	Size size = m_sprite->getContentSize();
	m_sprite->setPosition(Point(size.width*0.5f,size.height*0.5f));
	this->setContentSize(size);
	this->setAnchorPoint(Point(0.5f,0.5f));
}
void Entity::run(Action*act)
{
	if(m_sprite != NULL)
	{
		//ֹͣ������ж���
		this->stopAllActions();
		m_sprite->runAction(act); 
	}
}
bool Entity::isCollided(Entity*entity)
{
	//Small Plane�� player ������ײ
	if(/*this->getID() == std::string("Small Plane") &&*/ entity->getID() == std::string("Player"))
	{
		//��ȡ����
		Point playerCoord = entity->getPosition();
		Point monsterCoord = this->getPosition();
		//��ȡͼƬ��С
		Size playerSize = entity->getContentSize();
		Size monsterSize = this->getContentSize();
		//��ȡ�뾶
		float playerRadius = playerSize.height / 3 * 2.f;
		float monsterRadius = monsterSize.height / 3 * 2.f;
		//���ͼƬ����Բ������
		Point playerCenterRelative = Point(playerSize.width / 2,playerSize.height / 3);
		Point monsterCenterRealative = Point(monsterSize.width / 2,monsterSize.height / 3);
		//��ȡ��������
		Point playerCenterAbsolute = Point(playerCoord.x,playerCoord.y - 1.f/sqrt(3) * playerSize.width / 2);
		Point monsterCenterAbsolute = Point(monsterCoord.x,monsterCoord.y - 1.f/sqrt(3) * monsterSize.width /2);
		//��ȡ��Բ�ľ���
		float distance = sqrt(pow((playerCenterAbsolute.x - monsterCenterAbsolute.x),2) + pow((playerCenterAbsolute.y - monsterCenterAbsolute.y),2));
		//�����Բ���룬�˳��ж�
		if(playerRadius + monsterRadius <= distance)
			{
				return false;
		    }
		else
		{
			  /* log("Player has collidabled!!");
		log(Value(distance).asString().c_str());
		log(Value(playerRadius + monsterRadius).asString().c_str());
		*/
			//�Ƕ�
			double o = atan((playerCoord.y - monsterCoord.y)/(playerCoord.y - monsterCoord.y)) * 57.3f;
			double s1 = 2/3.f * playerSize.width * sin(60) / sin(120 - o);
			double s2 = 2/3.f * monsterSize.width * sin(60) / sin(120 - o);
			//û�ཻ
			if(s1 + s2 <= distance)
				return false;
			else
				return true;

		return true; 
		}
	}//�����
	//�л����ӵ�������ײ
	else if(/*this->getID() == std::string("Small Plane") &&*/ entity->getID() == std::string("Bullet"))
	{
		Point pos = entity->getPosition();
		Rect rect = this->getBoundingBox();

		return rect.containsPoint(pos);
	}

}
int Entity::getHitPoints()
{
	return m_hitPoints;
}
void Entity::setHitPoints(int HP)
{
	this->m_hitPoints = HP;
}
std::string Entity::getID()
{
	return m_id;
}
void Entity::setID(std::string str)
{
	this->m_id = str;
}