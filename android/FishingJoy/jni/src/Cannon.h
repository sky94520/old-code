#ifndef __Cannon_H__
#define __Cannon_H__
#include<cmath>
#include<string>
#include<vector>
#include<algorithm>
#include "Entity.h"

using namespace std;
/*Cannon�ǳ����ڵ㣬������GameScene����ΪCannonֻ��һ��
�����Ҳ������κ���ײ���*/
class CannonDelegate
{
public:
	virtual ~CannonDelegate(){}
	virtual void fireCallback(const Point&pos)=0;
};
class Cannon:public Node
{
public:
	enum class Type : int
	{
		None,
		Lv1,
		Lv2,
		Lv3,
		Lv4,
		Lv5,
		Lv6,
		Lv7,
		Laser = 11//��������
	};
	SDL_BOOL_SYNTHESIZE(m_bCanFire,CanFire);//�Ƿ�ɷ��䣬��Ҫ�ǵ�ǰ�Ĵ���״̬�Ƿ�ɷ��䣬�ͽ�ҵ��޹�
private:
	Type m_type;//��������
	Sprite*m_pSprite;//��������
	vector<Type> m_netBulletTypes;//�����ӵ�����
	Type m_lastType;//������һ������

	CannonDelegate*m_pDelegate;
public:
	Cannon();
	~Cannon();
	CREATE_FUNC(Cannon);
	bool init();
public:
	//��̨����
	void aimAt(const Point &target);
	//����
	void fire(const Point&pos);
	void fireEnd();//�������

	void addLevel();
	void subLevel();

	float getRotation()const;

	void setType(Type type);
	Type getType()const;

	void setDelegate(CannonDelegate*pDelegate);
	bool isBelongNetBulletType(Type type);//�Ƿ����������ӵ�����
	//��ȡ��ǹ���ȼ�
	int getNetGunBulletLv()const;
	//��ȡ��һ������
	Type getLastType()const;
	//������ǹ��������
	void setNetGunBullets(const vector<int>&vec);
private:
	string getSpriteName(Type type);//�������ͻ�ȡ���ھ�������
};
#endif