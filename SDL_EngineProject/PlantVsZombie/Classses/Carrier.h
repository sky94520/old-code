#ifndef __Carrier_H__
#define __Carrier_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
/*��������*/
enum class TerrainType
{
	None,
	Lawn,//�ݵ�
	Water,//ˮ��
	Stone,//ʯ��
	FlowerPot,//����
	LilyPad,//��Ҷ
};
class Plant;
class Defender;

class Carrier
{
	SDL_SYNTHESIZE(TerrainType,m_terrainType,TerrainType);//�õ��ε�����
	SDL_BOOL_SYNTHESIZE(m_bDestroyed,Destroyed);//��ǰ�ĵ����Ƿ񱻻ٻ�
	SDL_SYNTHESIZE(int,m_nRow,Row);
protected:
	Plant*m_pInnerPlant;
	Defender*m_pDefender;
public:
	Carrier();
	~Carrier();
	//�����ڲ�ֲ���������������
	void setInnerPlant(Plant*plant);
	//����ڲ�ֲ����ͷ���������
	void clearInnerPlant();
	Plant*getInnerPlant()const;
	//���ñ�����
	void setDefender(Defender*defender);
	Defender*getDefender()const;
	void clearDefender();
};
#endif