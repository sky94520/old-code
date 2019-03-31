#ifndef __Entity_H__
#define __Entity_H__
#include<tchar.h>
#include<Windows.h>
#include "common.h"

class Entity
{
	SYNTHESIZE(int,m_nNowHp,NowHp);//��ǰ����
	SYNTHESIZE(int,m_nMaxHp,MaxHp);//�������ֵ
	SYNTHESIZE(int,m_nNowMp,NowMp);//��ǰħ��ֵ
	SYNTHESIZE(int,m_nMaxMp,MaxMp);//���ħ��ֵ
	SYNTHESIZE(int,m_nLevel,Level);//��ǰ�ȼ�
	SYNTHESIZE(int,m_nStrength,Strength);//��ɫ����ֵ
	SYNTHESIZE(int,m_nIntelligence,Intelligence);//��ɫ����
	SYNTHESIZE(int,m_nAgility,Agility);//����
	SYNTHESIZE(LPCWSTR,m_textureID,TextureID);//��ͼID
	SYNTHESIZE(POINT,m_position,Position);//��ͼλ��
	SYNTHESIZE(SIZE,m_size,Size);//��ͼ��С
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