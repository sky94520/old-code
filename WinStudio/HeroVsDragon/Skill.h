#ifndef __Skill_H__
#define __Skill_H__
#include<Windows.h>
/*�������ܣ�����������ƺ��¼���Ӧ
������ι�����
��ξ��� �����ߣ���������
*/
class Skill
{
private:
	LPCWSTR m_name;//��������
	LPCWSTR m_desc;//��������
public:
	Skill();
	~Skill();
	bool load(LPCWSTR name,LPCWSTR desc);

	LPCWSTR getName()const;
	LPCWSTR getDesc()const;
};
#endif