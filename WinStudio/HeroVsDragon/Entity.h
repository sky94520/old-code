#ifndef __Entity_H__
#define __Entity_H__
#include<tchar.h>
#include<Windows.h>
#include "common.h"

class Entity
{
	SYNTHESIZE(int,m_nNowHp,NowHp);//当前生命
	SYNTHESIZE(int,m_nMaxHp,MaxHp);//最大生命值
	SYNTHESIZE(int,m_nNowMp,NowMp);//当前魔法值
	SYNTHESIZE(int,m_nMaxMp,MaxMp);//最大魔法值
	SYNTHESIZE(int,m_nLevel,Level);//当前等级
	SYNTHESIZE(int,m_nStrength,Strength);//角色力量值
	SYNTHESIZE(int,m_nIntelligence,Intelligence);//角色智力
	SYNTHESIZE(int,m_nAgility,Agility);//敏捷
	SYNTHESIZE(LPCWSTR,m_textureID,TextureID);//贴图ID
	SYNTHESIZE(POINT,m_position,Position);//贴图位置
	SYNTHESIZE(SIZE,m_size,Size);//贴图大小
public:
	Entity()
		:m_nNowHp(0),m_nMaxHp(0),m_nNowMp(0),m_nMaxMp(0),
		m_nLevel(0),m_nStrength(0),m_nIntelligence(0),m_nAgility(0)
	{}
	virtual~Entity(){}
	virtual BOOL load(int x,int y,int w,int h,LPCWSTR textureID)=0;
	virtual void draw(HDC hdc)=0;
	virtual void update()=0;
	virtual void clean()=0;
};
#endif