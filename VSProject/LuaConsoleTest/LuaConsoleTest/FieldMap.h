#ifndef __FieldMap_H__
#define __FieldMap_H__
#include<string>
#include<iostream>
#include "Value.h"
#include "Point.h"
#include "GlobalFunctions.h"

using namespace std;
class Monster;
class Player;
class FieldMap;
class FieldMapDelegate
{
public:
	virtual ~FieldMapDelegate(){}
	virtual void fight()=0;
	virtual void toggleLayer(const std::string&filename,const Point&playerPos)=0;
	virtual Player* getPlayer()const=0;
	virtual void setColliabledEntity(Colliabled*pColliabled)=0;
};
class TransferMatrix:public Colliabled
{
public:
	int x;
	int y;
	std::string mapFile;
	bool bAlived;
	FieldMap*m_pOwner;
public:
	TransferMatrix(int x=0,int y=0,const std::string&file="",bool alived=false)
		:x(x),y(y),mapFile(file),bAlived(alived),m_pOwner(nullptr){}
	virtual void collided();
	virtual std::string getName()const
	{
		return "传送阵";
	}
};
class FieldMap
{
	SDL_SYNTHESIZE(int,m_nStep,Step);//每多少步会遇到怪物
	SDL_SYNTHESIZE(std::string,m_name,Name);//地图名字
	SDL_SYNTHESIZE(std::string,m_descrption,Description);//地图描述
	SDL_SYNTHESIZE(int,m_nLevel,Level);
	SDL_SYNTHESIZE(int,m_nCurStep,CurStep);
private:
	vector<Monster*> m_monsterList;//怪物列表
	std::vector<Value> m_monsterStrs;//将会产生的怪物
	FieldMapDelegate*m_pDelegate;
	std::vector<TransferMatrix*> m_transferMatrixs;//传送阵
public:
	FieldMap();
	~FieldMap();
	virtual bool init(const std::string&filename);
	virtual void render();

	std::vector<Monster*>* getMonsters();
	void setDelegate(FieldMapDelegate*pDelegate);
	FieldMapDelegate*getDelegate()const;
private:
	void initTransferMatrix();
	void createMonsters();
};
#endif