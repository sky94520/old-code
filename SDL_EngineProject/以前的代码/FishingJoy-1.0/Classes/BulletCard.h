#ifndef __BulletCard_H__
#define __BulletCard_H__
#include "Entity.h"
#include "FishingJoyData.h"
class BulletCard:public Entity
{
private:
	BulletType m_type;
	int m_nBulletCount;//子弹数量
	Sprite*m_pDisabledSprite;//不可点击时显示的图片
	LabelAtlas*m_pLabel;//显示相应子弹的数目
public:
	BulletCard();
	~BulletCard();
	static BulletCard*create(BulletType type);
	bool init(BulletType type);
	//减少子弹数目函数,每次减少1
	bool subBulletCount();
	BulletCard*clone()const;
	bool isClicked()const;
	BulletType getType()const;
};
#endif