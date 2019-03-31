#ifndef __NeedfulFishCompent_H__
#define __NeedfulFishCompent_H__
#include "cocos2d.h"
USING_NS_CC;
class NeedfulFishCompent:public Node
{
	CC_SYNTHESIZE(Point,m_compPosition,CompPosition);//组件所在的位置，该位置一经赋值后就不再修改
private:
	Sprite*m_pSprite;
	Sprite*m_pBG;//背景
	Label*m_pLabel;
	int m_nCount;
public:
	NeedfulFishCompent();
	~NeedfulFishCompent();
	static NeedfulFishCompent*create(int id,int num);
	bool init(int id,int num);
	//设置当前数量
	void setCount(int count);
	int getCount()const;
};
#endif