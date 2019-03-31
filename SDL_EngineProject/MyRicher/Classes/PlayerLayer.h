#ifndef __PlayerLayer_H__
#define __PlayerLayer_H__
#include <string>
#include <vector>
#include "SDL_Engine/SDL_Engine.h"
#include "lua/lua.h"
using namespace std;
using namespace SDL;
class Player;

class PlayerLayer : public Layer
{
private:
	vector<Player*> m_players;
	int m_nCurPlayer;//当前正在执行的角色索引
	bool m_bRoundOver;//回合是否结束
public:
	PlayerLayer();
	~PlayerLayer();
	CREATE_FUNC(PlayerLayer);
	bool init();
	void update(float dt);
	//创建主角动画
	void createAnimationOfPlayer(Texture*texture,const string& playerName);
	//添加主角
	void addPlayer(Player* player);
};
#endif