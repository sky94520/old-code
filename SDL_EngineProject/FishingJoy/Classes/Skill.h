#ifndef __Skill_H__
#define __Skill_H__

#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;

class Fish;

class Skill
{
	SDL_SYNTHESIZE(float,m_rate,Rate);//�ɹ������ļ���
	SDL_SYNTHESIZE(float,m_duration,Duration);//���ܳ���ʱ��
public:
	Skill()
		:m_rate(0.f),m_duration(0.f)
	{}

	virtual void skillEnter(Fish*fish)=0;
	virtual void skillExit(Fish*fish)=0;
};
//-----------------------SkillNothing--------------------------
class SkillNothing:public Skill
{
public:
	SkillNothing(float rate,float duration);

	virtual void skillEnter(Fish*fish);
	virtual void skillExit(Fish*fish);
};
//-------------------------SkillSpeedUp---------------------------------
class SkillSpeedUp:public Skill
{
public:
	SkillSpeedUp(float rate,float duration);
	virtual void skillEnter(Fish*fish);
	virtual void skillExit(Fish*fish);
};
//------------------------SkillScared-----------------------------------
class SkillScared:public Skill
{
public:
	SkillScared(float rate);
	virtual void skillEnter(Fish*fish);
	virtual void skillExit(Fish*fish);
};
//------------------------SkillInvulnerable---------------------------------
class SkillInvulnerable:public Skill
{
public:
	SkillInvulnerable(float rate,float duration);

	virtual void skillEnter(Fish*fish);
	virtual void skillExit(Fish*fish);
};
#endif