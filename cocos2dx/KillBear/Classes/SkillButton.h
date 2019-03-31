#ifndef __SkillButton_H__
#define __SkillButton_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
class SkillButton : public Node
{
private:
	//技能按钮
	ui::Button*m_pButtonSkill;
	//蒙版按钮
	Sprite*m_pMask;
	//进度条
	ProgressTimer*m_pProgressTimer;
	//冷却时间
	//float m_fCDTime;
	Label*m_pCurTimeLabel;
	//总cd时间
	float m_fCDTime;
	//current cd time
	CC_SYNTHESIZE(float,m_fCurCDTime,CurCDTime);
public:
	SkillButton();
	~SkillButton();

	static SkillButton*create(const char*normalFile,const char*selectedFile,const char*mask,float cdTime);
	bool init(const char*nomalFile,const char*selectedFile,const char*mask,float cdTime);
private:
	//冷却时间显示定时器
	void coolDownReduce(float dt);

	//回调函数
	void clickCallback(Ref*);
	void coolDownCallback(Node*pNode);
};
#endif