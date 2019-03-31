#ifndef __Skill_H__
#define __Skill_H__
#include<Windows.h>
/*描述技能，并不参与绘制和事件响应
技能如何攻击？
如何决定 攻击者，被攻击者
*/
class Skill
{
private:
	LPCWSTR m_name;//技能名称
	LPCWSTR m_desc;//技能描述
public:
	Skill();
	~Skill();
	bool load(LPCWSTR name,LPCWSTR desc);

	LPCWSTR getName()const;
	LPCWSTR getDesc()const;
};
#endif