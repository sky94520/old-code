#ifndef __DynamicData_H__
#define __DynamicData_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
#define RESSURECT_CSV_PATH "csv/playerressurect.csv"
#define LIFE_CSV_PATH "csv/playerlife.csv"
/*����csv��Ӧ������*/
enum RessurectProp
{
	kRessurectProp_ID,
	kRessurectProp_Level,
	kRessurectProp_State,
	kRessurectProp_Worth,
};
/*����csv��Ӧ������*/
enum LifeProp
{
	kLifeProp_ID,
	kLifeProp_Level,
	kLifeProp_State,
	kLifeProp_Worth,
};
class DynamicData
{
	SDL_SYNTHESIZE(int,m_nPlayerLives,PlayerLives);//��������
	SDL_SYNTHESIZE(int,m_nPlayerMaxHp,PlayerMaxHp);//���ǵ��������ֵ
	SDL_SYNTHESIZE(float,m_nPlayerInvulnerableTime,PlayerInvulnerableTime);//���ǵ��޵�ʱ��
	SDL_SYNTHESIZE(float,m_playerSpeed,PlayerSpeed);//���ǵ��ƶ��ٶ�
	SDL_SYNTHESIZE(int,m_gold,Gold);//���ǽ��

	SDL_SYNTHESIZE(int,m_lifeLevel,LifeLevel);//���������ȼ�
	SDL_SYNTHESIZE(int,m_ressurectLevel,RessurectLevel);//���Ǹ�����޵еȼ�
private:
	static DynamicData*m_pInstance;
	DynamicData();
	~DynamicData();
public:
	static DynamicData*getInstance()
	{
		if(m_pInstance == nullptr)
			m_pInstance = new DynamicData();
		return m_pInstance;
	}
	void purge();
	
	bool alterPlayerLives(int life);//���ӻ��߼�������ֵ ͬʱ�ᷢ��֪ͨ
	bool alterPlayerGold(int gold);//���ӻ��߼��ٽ�� ͬʱ�ᷢ��֪ͨ
	void reset();

	int getPlayerLives(int level);
	int getNextLifeLevel();//��ȡ��һ���ȼ�������ǰ�Ѿ��������һ��������-1
	int getWorthByLifeLevel(int curLifeLevel);//���ݵ�ǰ�������ȼ���ü�ֵ
};
#endif