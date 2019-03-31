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
	int m_nCurPlayer;//��ǰ����ִ�еĽ�ɫ����
	bool m_bRoundOver;//�غ��Ƿ����
public:
	PlayerLayer();
	~PlayerLayer();
	CREATE_FUNC(PlayerLayer);
	bool init();
	void update(float dt);
	//�������Ƕ���
	void createAnimationOfPlayer(Texture*texture,const string& playerName);
	//�������
	void addPlayer(Player* player);
};
#endif