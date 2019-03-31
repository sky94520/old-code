#ifndef __BulletCard_H__
#define __BulletCard_H__
#include "Entity.h"
#include "FishingJoyData.h"
class BulletCard:public Entity
{
private:
	BulletType m_type;
	int m_nBulletCount;//�ӵ�����
	Sprite*m_pDisabledSprite;//���ɵ��ʱ��ʾ��ͼƬ
	LabelAtlas*m_pLabel;//��ʾ��Ӧ�ӵ�����Ŀ
public:
	BulletCard();
	~BulletCard();
	static BulletCard*create(BulletType type);
	bool init(BulletType type);
	//�����ӵ���Ŀ����,ÿ�μ���1
	bool subBulletCount();
	BulletCard*clone()const;
	bool isClicked()const;
	BulletType getType()const;
};
#endif