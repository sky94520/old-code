#ifndef __GoldCounter_H__
#define __GoldCounter_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
/*金币计数器*/
class GoldCounter:public Node
{
private:
	//当前金币数量
	unsigned int m_nCoinCount;
	//显示当前金币数量的Label
	LabelAtlas*m_pLabel;
public:
	GoldCounter();
	~GoldCounter();
	CREATE_FUNC(GoldCounter);
	bool init();
public:
	//增加金币数量
	void addCoinCount(Object*obj);
	//减少金币数量
	void subCoinCount(Object*obj);
private:
	std::string getCoinCountString();
};
#endif