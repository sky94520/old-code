#ifndef __SaveData_H__
#define __SaveData_H__
#include "cocos2d.h"
USING_NS_CC;

class SaveData : public Ref
{
public:
	static SaveData*getInstance();
	virtual bool init();

	SaveData();
	~SaveData();
public:
	long getGold();
	void setGold(long iGold);

	long getScore();
	void setScore(long iScore);
private:
	static SaveData*m_saveData;
	//���
	long int m_gold;
	//����
	long int m_score;
};
#endif