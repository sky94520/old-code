#ifndef __DoubleColumn_H__
#define __DobuleColumn_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
class Column;
class DoubleColumn:public Node
{
private:
	Column*m_pTop;
	Column*m_pBottom;
public:
	DoubleColumn();
	~DoubleColumn();
	CREATE_FUNC(DoubleColumn);
	bool init();
	//���ã���֤������
	void reset();
	//�Ƿ���ã����Ƿ����
	bool isAvaiable()const;
	//�Ƿ����rect������ײ
	bool checkCollision(const Rect&rect);
};
#endif