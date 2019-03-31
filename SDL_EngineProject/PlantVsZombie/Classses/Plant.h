#ifndef __Plant_H__
#define __Plant_H__
#include<string>
#include "Character.h"
#include "StaticData.h"

using namespace std;
class Carrier;
class Garnishry;
class ZombieBase;
class ShooterPeaBullet;

/*ֲ������*/
enum class PlantType
{
	Common,//��ͨ��ֲ��
	NightPlant,//ҹ��ֲ��
	Vessel,//������ֲ��
	Defender,//������ֲ��
};

class PlantDelegate
{
public:
	virtual ~PlantDelegate(){}
	virtual void makeSun(int number,FiniteTimeAction*action,const Point&bornPos)=0;
	virtual void confuseZombie(ZombieBase*zombie) = 0;
	virtual ZombieBase*findFirstZombieOfRow(int row,Direction attackDir,const Point&pos) = 0;
	virtual void showRisingDirt(const Point&pos,int localZOrder) = 0;

	virtual ZombieBase*findFirstCollidedZombie(int row,const Rect&rect) = 0;
	virtual vector<ZombieBase*> findCollidedZombies(int row,const Rect& rect) = 0;
	virtual ZombieBase* findFirstZombieOfIronGarnishry(const Rect& rect) = 0;

	virtual ShooterPeaBullet* findFirstShooterPeaBullet(int row,const Rect&rect) = 0;
	virtual vector<Terrain*>& getTerrainsOfRow(int row) = 0;

	virtual void showExplosionSpudow(const Point&pos) = 0;
	virtual void showSnow() = 0;
	virtual void showBoom(const Point&pos) = 0;
	virtual void showFire(const Point&pos,int localZOrder) = 0;
	//�����Ʒ��Ч
	virtual void addGarnishryEffect(int uniqueID,const Point&pos,Garnishry*garnishry) = 0;
	virtual void removeGarnishryEffect(int uniqueID) = 0;

	virtual void addBoom(int damage,int row,const Rect&rect)=0;
	virtual void addPeaBullet(int damage,int row,const Point&startPos,bool bRight = true) = 0;
	virtual void addSnowPeaBullet(int damage,int row,const Point&startPos)=0;
	virtual void addFirePeaBullet(int damage,int row,const Point&startPos)=0;

	virtual void addCabbageBullet(ZombieBase*zombie,int damage,int row,const Point&startPos)=0;
	virtual void addCornpultBullet(ZombieBase*zombie,bool isButter,int damage,int row,const Point&startPos)=0;
	virtual void addShroomBullet(int damage,int row,const Point& startPos,float atkScope) = 0;
	virtual void addFumeShroomBullet(int damage,int row,const Point&startPos,float atkScope)=0;

	virtual Rect getGameVisibleRect() = 0;
};

class Plant : public Character
{
	SDL_SYNTHESIZE(float,m_fColdDownTime,ColdDownTime);//��cd
	SDL_SYNTHESIZE(ActiveTime,m_activeTime,ActiveTime);//�ʱ��
	SDL_SYNTHESIZE(string,m_plantName,PlantName);//ֲ������
	SDL_SYNTHESIZE(PlantType,m_plantType,PlantType);//ֲ������
protected:
	PlantDelegate*m_pDelegate;
	Plant*m_pVesselPlant;//������ֲ�� TODO
	Carrier*m_pCarrier;//������ֲ������Ӧ������,�����ҵ�����
public:
	Plant();
	~Plant();

	void setDelegate(PlantDelegate*delegate);
	void hurt(int damage,AttackType attackType);

	//��������������
	void setLocatedCarrier(Carrier*carrier);
	//��ȡ����������
	Carrier*getLocatedCarrier();
	//��ȡֲ�����ڵ���
	virtual int getRow()const;
	virtual void update(float dt);
	virtual void onHurt();
	//����ʬ��ʱ����
	virtual void eatenByZombie(ZombieBase*zombie);
	virtual Rect getCollisionBoundingBox()const;

	void setVesselPlant(Plant*plant);
	Plant*getVesselPlant()const;
protected:
	//ÿ�θ��¶�����õĹ��Ӻ���
	virtual void updateHook(float dt) = 0;
};
#endif