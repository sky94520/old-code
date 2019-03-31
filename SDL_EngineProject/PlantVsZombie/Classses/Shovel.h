#ifndef __Shovel_H__
#define __Shovel_H__
#include "SDL_Engine/SDL_Engine.h"
#include "Entity.h"

using namespace SDL;
class Shovel : public Entity
{
private:
	//��ǰ�Ƿ���ѡ��״̬
	bool m_bSelected;
public:
	Shovel();
	~Shovel();
	CREATE_FUNC(Shovel);
	bool init();
	//�Ƿ�ѡ��
	bool isSelected()const;
	//����Ϊѡ��״̬
	void selected();
	//����Ϊûѡ��״̬
	void unselected();
};
#endif