#ifndef __NeedfulFishCompent_H__
#define __NeedfulFishCompent_H__
#include "cocos2d.h"
USING_NS_CC;
class NeedfulFishCompent:public Node
{
	CC_SYNTHESIZE(Point,m_compPosition,CompPosition);//������ڵ�λ�ã���λ��һ����ֵ��Ͳ����޸�
private:
	Sprite*m_pSprite;
	Sprite*m_pBG;//����
	Label*m_pLabel;
	int m_nCount;
public:
	NeedfulFishCompent();
	~NeedfulFishCompent();
	static NeedfulFishCompent*create(int id,int num);
	bool init(int id,int num);
	//���õ�ǰ����
	void setCount(int count);
	int getCount()const;
};
#endif