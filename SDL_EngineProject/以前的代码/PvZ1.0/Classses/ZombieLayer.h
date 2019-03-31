#ifndef __ZombieLayer_H__
#define __ZombieLayer_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
using namespace rapidxml;
class Zombie;
class ZombieLayer:public Layer
{
private:
	Vector<Zombie*> *m_zombies[5];//��������·�ϵĽ�ʬ
	Vector<Zombie*> m_notShowZombies;//δ���ֵĽ�ʬ
public:
	ZombieLayer();
	~ZombieLayer();
	CREATE_FUNC(ZombieLayer);
	bool init();
	//��rapidxml�����ļ�
	bool createZombiesFromXml(const std::string&filepath);

	virtual void update(float dt);
	Vector<Zombie*>* getZombies(int line = 0)const
	{
		return m_zombies[line];
	}
};
#endif