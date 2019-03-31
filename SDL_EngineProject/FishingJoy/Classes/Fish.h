#ifndef __Fish_H__
#define __Fish_H__
#include<map>
#include<string>
#include<functional>
#include "B2Entity.h"

using namespace std;

enum class TriggingType
{
	None,
	NetGunBullet,//����ǹ��������ײ
	Fishing,//�Ͳ������͵ķ�����ײ
	GroupCome,//�㳱����
};

enum class FishType
{
	Fish,
	StarFish,/*����*/
};

class Skill;

class Fish:public B2Entity
{
public:
	enum class State
	{
		None,
		Running,//�˶�״̬
		Skill,//����״̬
		Caught,//����׽״̬
	};
	static const int FISH_ANIMATION_TAG;

	SDL_SYNTHESIZE(unsigned int,m_nID,ID);
	SDL_SYNTHESIZE(State,m_state,State);//��ǰ���״̬
	SDL_SYNTHESIZE(float,m_speed,Speed);//�ٶ�
	SDL_SYNTHESIZE(float,m_duration,Duration);//���ܳ���ʱ��
	SDL_SYNTHESIZE(FishType,m_fishType,FishType);//�������
private:
	map<TriggingType,Skill*> m_skills;
	
	TriggingType m_triggingType;
	bool m_bInvulnerable;//�Ƿ����޵�
	function<void (Fish*)> m_deadCallback;//�����ص�����
public:
	Fish();
	~Fish();
	CREATE_FUNC(Fish);
	static Fish*create(int id);
	bool init();
	bool init(int id);
	void setSkills(const map<TriggingType,Skill*>&skills);
	bool isInvulnerable()const;
	void setInvulnerable(bool invulnerable);
	void setDeadCallback(const function<void (Fish*)>&callback);
public:
	virtual void update(float dt);
	virtual void reset();
	virtual void clear();

	virtual void caught();//����׽�ص�����
	virtual void collided(TriggingType type);//��ײ�ص�����

	//�����ص�����
	void dead();
};
#endif