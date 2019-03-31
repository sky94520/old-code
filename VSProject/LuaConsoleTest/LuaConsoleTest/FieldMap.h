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
		return "������";
	}
};
class FieldMap
{
	SDL_SYNTHESIZE(int,m_nStep,Step);//ÿ���ٲ�����������
	SDL_SYNTHESIZE(std::string,m_name,Name);//��ͼ����
	SDL_SYNTHESIZE(std::string,m_descrption,Description);//��ͼ����
	SDL_SYNTHESIZE(int,m_nLevel,Level);
	SDL_SYNTHESIZE(int,m_nCurStep,CurStep);
private:
	vector<Monster*> m_monsterList;//�����б�
	std::vector<Value> m_monsterStrs;//��������Ĺ���
	FieldMapDelegate*m_pDelegate;
	std::vector<TransferMatrix*> m_transferMatrixs;//������
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