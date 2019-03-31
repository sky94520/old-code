#ifndef __FishingNet_H__
#define __FishingNet_H__
#include "B2Entity.h"
#include "Cannon.h"

//����ľ�������
enum class FishingType : int
{
	None,
	FishingNet,
	Pearl,
	Fog,
	Laser = 11//��������
};
/*todo*/
class FishingEntity:public B2Entity
{
protected:
	FishingType m_fishingType;
public:
	FishingEntity();
	virtual float showAt()=0;
	virtual void collided()=0;

	FishingType getFishingType()const;
	void setFishingType(FishingType fishingType);
};

class FishingNet:public FishingEntity
{
	SDL_SYNTHESIZE(int,m_nLv,Level);//��ǰ�ȼ�
public:
	FishingNet();
	~FishingNet();
	CREATE_FUNC(FishingNet);
	static FishingNet*create(int lv);
	bool init();
	bool initWithLv(int lv);
public:
	virtual float showAt();
	virtual void collided();
};
//-------------------------Laser------------------------------
class Laser : public FishingEntity
{
public:
	CREATE_FUNC(Laser);
	bool init();

	virtual float showAt();
	virtual void collided();
};
#endif