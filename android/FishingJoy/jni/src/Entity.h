#ifndef __Entity_H__
#define __Entity_H__
#include<string>
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
using namespace std;

class Entity:public Node
{
public:
	enum class Type
	{
		None,
		Fishing,//���㹦��
		Fish,//��
		Bullet,//��ǹ��
	};
	SDL_SYNTHESIZE(int,m_nHP,HP);//��ǰѪ��
	SDL_SYNTHESIZE(Type,m_type,Type);//��ȡ��ǰʵ������
	SDL_BOOL_SYNTHESIZE(m_bDead,Dead);//�Ƿ�����������������Ļ����ʧ
protected:
	Sprite*m_pSprite;
public:
	Entity();
	~Entity();
	Sprite*getSprite()const;
	void bindSprite(Sprite*sprite);
	bool bindSpriteWithSpriteFrameName(const string&spriteName);
	//��ײ��������ֻҪ������ײ������ص��������
	virtual void collided();
	//��������
	static Animate*createAnimate(std::string format,int begin,int end,float delayPerUnit,unsigned int loops=-1);
};
#endif