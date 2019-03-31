#ifndef __SplitPea_H__
#define __SplitPea_H__

#include "Pea.h"

class SplitPea : public Pea
{
private:
	float m_elapsed;
	int m_nCurBulletNum;
	int m_nBulletNumber;
public:
	SplitPea();
	~SplitPea();
	static SplitPea*create(const string& plantName);
	bool init(const string& plantName);
protected:
	virtual void updateAttackState(float dt);
	virtual void updateAttackEndState(float dt);
};
#endif