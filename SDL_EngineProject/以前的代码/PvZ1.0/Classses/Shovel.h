#ifndef __Shovel_H__
#define __Shovel_H__
#include "SDL_Engine/SDL_Engine.h"
#include "Shovel.h"
using namespace SDL;
class Shovel : public Node
{
private:
	Sprite*m_pBackground;//����
	Sprite*m_pSprite;//����
	//ѡ��?
	bool m_bSelected;
public:
	Shovel();
	~Shovel();
	CREATE_FUNC(Shovel);
	bool init();
	//����
	void clear();
	//�Ƿ�ѡ��
	bool isSelected()const;
	void setSelected(bool seleced);
	Sprite* getSprite()const;

	
	void runBlinkAction();
	void runKillPlantAction(const Point&pos);//����Ϊ��������
};
#endif