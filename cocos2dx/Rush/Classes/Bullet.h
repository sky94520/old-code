#ifndef __Bullet_H__
#define __Bullet_H__
#include "cocos2d.h"
class Monster;
USING_NS_CC;
enum FlyTrajectory
{
	kTrajectory_straight,
	kTrajectory_curve
};
enum EnumBulletPropConfType
{
	enBulletPropConfType_ID,
	enBulletPropConfType_Name,
	enBulletPropConfType_Type,
	enBulletPropConfType_RunFrame,
	enBulletPropConfType_AtkFrame,
	enBulletPropConfType_Resource
};
class Bullet : public Node
{
private:
	Sprite*m_pSprite;

	Point m_startPos;
	Point m_endPos;
	// mark the bullet is used
	bool m_bIsUsed;
	//the bullet arrive the end
	bool m_bIsArrived;
	void bindSprite(Sprite*sprite);
	Size m_colliableSize;
	//resource
	std::string resource_name;
	int m_nRunFrame;
	int m_nAtkFrame;
public:
	Bullet();
	~Bullet();
	bool initWithCsvFileByID(int nBulletID);
	static Bullet* createFromCsvFileByID(int nBulletID);
	//set the way
	void setRoute(Point startPos,Point endPos);
	void start();
	//the function is virtual,it is extended by its son
	virtual void attack();

	CC_SYNTHESIZE(float,m_nAtkValue,AtkValue);
	CC_SYNTHESIZE(float,m_nMoveDuration,MoveDuration);
	//aim
	CC_SYNTHESIZE(Monster*,m_pAtkMonster,AtkMonster);
	//animate
	CC_SYNTHESIZE_RETAIN(Animation*,m_pAtkAnimation,AtkAnimation);//attack animation
	CC_SYNTHESIZE_RETAIN(Action*,m_pRunAction,RunAction);//run animation
};
#endif
