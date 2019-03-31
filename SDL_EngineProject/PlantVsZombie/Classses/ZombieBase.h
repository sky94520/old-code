#ifndef __ZombieBase_H__
#define __ZombieBase_H__
#include<string>
#include<vector>
#include<algorithm>
#include "Character.h"

using namespace std;

class HpBar;
class Plant;
class Terrain;
class MoveBehavior;
class Garnishry;
class Bullet;
class ZombieBase;

class ZombieDelegate
{
public:
	virtual Plant*getTopPlant(Terrain*terrain) = 0;
	
	virtual void addButterSplat(const Point&pos,int localZOrder,int uniqueID)=0;
	virtual void removeButterSplat(int uniqueID)=0;

	virtual void addIceTrap(const Point&pos,int localZOrder,int uniqueID)=0;
	virtual void removeIceTrap(int uniqueID)=0;

	virtual void showRisingDirt(const Point&pos,int localZOrder) = 0;

	virtual void showZombieDie(const string& zombieName,const Point&pos,int localZOrder,bool flipX) = 0;
	virtual void showZombieBoom(const string& zombieName,const Point&pos,int localZOrder,bool flipX) = 0;
	virtual void showZombieHead(const string& zombieName,const Point&pos,int localZOrder,bool flipX) = 0;
	virtual void showGarnishryFallAction(Garnishry*garnishry,const Point&pos,int localZOrder,bool flipX) = 0;

	virtual ZombieBase*makeZombie(const string& zombieName,const Point&pos,int row,bool bConfused) = 0;
};
/*��ʬ�ļ���Ч��*/
enum class DebuffType
{
	Deceleration,
	Butter,
	Ice,
};
typedef struct Debuff
{
	DebuffType type;
	float duration;
public:
	Debuff(DebuffType type,float d):type(type),duration(d){}
}Debuff;

class ZombieBase : public Character
{
	SDL_SYNTHESIZE(float,m_fCriticalPoint,CriticalPoint);//�ٽ��
	SDL_SYNTHESIZE(float,m_fBaseSpeed,BaseSpeed);//�����ƶ��ٶ�
	SDL_SYNTHESIZE(string,m_zombieName,ZombieName);//��ʬ����
	SDL_SYNTHESIZE(float,m_fColdDownTime,ColdDownTime);//������ȴʱ��
	SDL_SYNTHESIZE(int,m_nDamage,Damage);//�˺�ֵ
	SDL_BOOL_SYNTHESIZE(m_bConfused,Confused);//�Ƿ��Ի�
protected:
	Character*m_pAim;//��ǰĿ��
	ZombieDelegate*m_pDelegate;
	MoveBehavior*m_pMoveBehavior;
	HpBar*m_pHpBar;
	Garnishry*m_pGarnishry;//��Ʒ
	vector<Debuff> m_debuffs;//��ǰ�Ľ�ʬ��debuff
	int m_nRow;
	Rect m_vertexBox;//�����Χ��
private:
	float m_eatingElapsed;
	bool _isDying;//��ǰ��ʬ�Ƿ��Ѿ�����
public:
	ZombieBase();
	~ZombieBase();
	//����ί��
	void setDelegate(ZombieDelegate*pDelegate);
	//���õ�ǰ����
	void setRow(int row);
	//���õ�ǰĿ��
	void setAim(Character*character);
	Character*getAim();
	//���Ŀ��
	void clearAim();
	//��Ŀ��
	void eatAim(float dt);
	//�����Ʒ
	void addGarnishry(Garnishry*garnishry);
	//�Ƴ���Ʒ
	//void removeGarnishry(Garnishry*garnishry);
	Garnishry*getGarnishry();
	//���Ǹ������������ٽ��
	bool isDying()const;
	//���ö����Χ��
	void setVertexBox(const Rect&rect);
	Rect getVertexBox()const;

	virtual Rect getCollisionBoundingBox()const;
	//��д���˻ص�����
	void hurt(int baseDamage,AttackType attackType);
	//����
	void deceleration(AttackType type,float duration);
	//����
	void butter(const Point&pos,float duration);
	//����
	void ice(float duration);
	//�����ƶ���Ϊ
	void setMoveBehavior(MoveBehavior*behavior);
	MoveBehavior*getMoveBehavior();
	//��Ѫ����
	void bindHpBar(HpBar*hpBar);
	//�Ƿ���ĳһ��debuff��
	bool isDuringDebuff(DebuffType debuffType)const;
	//�Ƿ��ڼ���״̬
	bool isDuringDeceleration()const;
	//���ڻ���״̬
	bool isDuringButter()const;
	//�Ƿ��ڱ���״̬
	bool isDuringIce()const;
	//�Ƿ���ͣ �����ڻ��ͻ��߱���debuffʱ��������ͣ״̬
	bool isPausedLogic()const;
	//��ȡ��ǰ����
	virtual int getRow()const;
	//��ȡ��ǰ�ٶ�
	virtual float getCurSpeed()const;
	//���»ص�����
	virtual void update(float dt);
	//�Ƿ�������ӵ�����ײ��������Boom
	virtual bool isActiveForBullet()const;
	//�ı���ͼΪ��
	virtual void setSpriteFlipX(bool flipX);
protected:
	//���Ÿ��º���
	virtual void updateAlive(float dt) = 0;
	//��ʬ�Ƿ���ƶ�
	virtual bool isCanMove()const;
	//���˻ص�����
	virtual void onHurt();
	//���������ص�����
	virtual void onSwallowDead();
	//ը���ص�����
	virtual void onBoomDead();
	//�����ص�����
	virtual void onNormalDead();
	//�ٽ��������Ϊ0�ص�����
	virtual void onCRPDead();
	//��Ʒ��������
	virtual void onGarnishryDead();
	//����debuff��ʼ�������뾭��Speed��װ
	virtual void onDecelerationDebuffEnter();
	//����debuff����
	virtual void onDecelerationDebuffExit();
	//����debuff���� ��ʼ
	virtual void onButterDebuffEnter(const Point&pos);
	//����debuff���� ����
	virtual void onButterDebuffExit();
	//������ʼ
	virtual void onIceDebuffEnter();
	virtual void onIceDebuffExit();
private:
	//���˶���
	void showHurtAction();
	//����ĳһ���͵�debuff
	void removeDebuff(DebuffType debuffType);
	vector<Debuff>::iterator removeDebuff(vector<Debuff>::iterator it);
	void removeAllDebuff();
	//�������debuff
	void  addDebuff(Debuff debuff,const function<void ()> &callback);
	void updateDebuff(float dt);
protected:
	//�л���������
	void changeAnimation(Animation*animation);
};
#endif