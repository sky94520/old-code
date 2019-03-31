#ifndef __GoldCounter_H__
#define __GoldCounter_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
/*��Ҽ�����*/
class GoldCounter:public Node
{
private:
	//��ǰ�������
	unsigned int m_nCoinCount;
	//��ʾ��ǰ���������Label
	LabelAtlas*m_pLabel;
public:
	GoldCounter();
	~GoldCounter();
	CREATE_FUNC(GoldCounter);
	bool init();
public:
	//���ӽ������
	void addCoinCount(Object*obj);
	//���ٽ������
	void subCoinCount(Object*obj);
private:
	std::string getCoinCountString();
};
#endif