#ifndef __Player_H__
#define __Player_H__
#include "Entity.h"
enum class Direction;

class Player : public Entity
{
	SDL_SYNTHESIZE(string,m_playerName,PlayerName);//��ɫ����
	SDL_SYNTHESIZE(int,m_nMoney,Money);//��Ǯ
	SDL_SYNTHESIZE(int,m_nStrength,Strength);//����
	SDL_BOOL_SYNTHESIZE(m_bDelegated,Delegated);//�Ƿ��йܸ�AI
private:
	Direction m_direction;
public:
	Player();
	~Player();
	static Player* create(const string& name,Direction dir);
	bool init(const string& name,Direction dir);
};
#endif