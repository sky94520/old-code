#ifndef __Fork_H__
#define __Fork_H__
#include<vector>
#include "Entity.h"
class Fork : public Entity
{
private:
	bool m_bShooting;//��ǰ����Ƿ����ڲ���
	Point m_targetPos;//Ŀ���
public:
	Fork();
	~Fork();
	CREATE_FUNC(Fork);
	bool init();
	//���� targetPos ��������
	void shoot(const Point&targetPos);
	//��ȡ��Ч��ײ��Χ��Ϊ��������
	virtual Rect getColliableRect()const;

	std::vector<Rect> getColliableRects()const;

	void setShooting(bool shooting);
	bool isShooting()const;
};
#endif