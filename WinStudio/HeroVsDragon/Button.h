#ifndef __Button_H__
#define __Button_H__
#include<Windows.h>
/*�򵥰�ť���ý�����Ϣ*/
/*��Ϣ����������������ƶ�ʱ
1.���δ��� �ж��Ƿ����-�������ʾ������ϸ
2.����Ѿ���磬�������-----����ʾ������ϸ*/
class Skill;
class Button
{
private:
	/*������ͼ*/
	LPCWSTR m_pNormalID;
	RECT m_rect;
	bool m_bShowDetail;//�Ƿ���ʾ��ϸ
	Skill*m_pSkill;//����
public:
	Button();
	~Button();

	virtual bool load(int x,int y,int w,int h,LPCWSTR textureID);
	virtual void draw(HDC hdc);
	virtual void update();
	virtual void clean();
	//����Ӧ����
	void bindSkill(Skill*pSkill);
	//��Ӧ����ƶ�
	void mouseMove(DWORD x,DWORD y);
	//��Ӧ��갴��
	void mouseLBDown(DWORD x,DWORD y);
};
#endif