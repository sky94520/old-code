#ifndef __SkillButton_H__
#define __SkillButton_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
class SkillButton : public Node
{
private:
	//���ܰ�ť
	ui::Button*m_pButtonSkill;
	//�ɰ水ť
	Sprite*m_pMask;
	//������
	ProgressTimer*m_pProgressTimer;
	//��ȴʱ��
	//float m_fCDTime;
	Label*m_pCurTimeLabel;
	//��cdʱ��
	float m_fCDTime;
	//current cd time
	CC_SYNTHESIZE(float,m_fCurCDTime,CurCDTime);
public:
	SkillButton();
	~SkillButton();

	static SkillButton*create(const char*normalFile,const char*selectedFile,const char*mask,float cdTime);
	bool init(const char*nomalFile,const char*selectedFile,const char*mask,float cdTime);
private:
	//��ȴʱ����ʾ��ʱ��
	void coolDownReduce(float dt);

	//�ص�����
	void clickCallback(Ref*);
	void coolDownCallback(Node*pNode);
};
#endif