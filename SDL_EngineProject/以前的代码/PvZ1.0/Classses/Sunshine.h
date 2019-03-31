#ifndef __Sunshine_H__
#define __Sunshine_H__
#include "Entity.h"
typedef enum SunshineType
{
	kSunshineType_15 = 15,//15
	kSunshineType_25 = 25
}SunshineType;
class Sunshine:public Entity
{
	SDL_SYNTHESIZE(float,m_elapsed,Elapsed);//����ֵ
	SDL_SYNTHESIZE(SunshineType,m_type,SunshineType);//̫������
private:
	bool m_bArriveLawn;//�Ƿ񵽴����
	bool m_bCollected;//�Ƿ��ռ�
public:
	Sunshine();
	~Sunshine();
	static Sunshine*create(SunshineType type);
	bool init(SunshineType type);

	bool isArriveLawn()const;
	void setArriveLawn(bool ret);

	bool isCollected()const;
	void setCollected(bool collected);
};
#endif