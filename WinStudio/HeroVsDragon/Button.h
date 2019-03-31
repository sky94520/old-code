#ifndef __Button_H__
#define __Button_H__
#include<Windows.h>
/*简单按钮，得接收消息*/
/*消息驱动，当发生鼠标移动时
1.如果未入界 判断是否入界-入界则显示技能详细
2.如果已经入界，如果出界-----不显示技能详细*/
class Skill;
class Button
{
private:
	/*正常贴图*/
	LPCWSTR m_pNormalID;
	RECT m_rect;
	bool m_bShowDetail;//是否显示详细
	Skill*m_pSkill;//技能
public:
	Button();
	~Button();

	virtual bool load(int x,int y,int w,int h,LPCWSTR textureID);
	virtual void draw(HDC hdc);
	virtual void update();
	virtual void clean();
	//绑定相应技能
	void bindSkill(Skill*pSkill);
	//响应鼠标移动
	void mouseMove(DWORD x,DWORD y);
	//相应鼠标按键
	void mouseLBDown(DWORD x,DWORD y);
};
#endif