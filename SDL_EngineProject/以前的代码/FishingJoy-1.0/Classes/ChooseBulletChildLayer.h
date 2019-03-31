#ifndef __ChooseBulletChildLayer_H__
#define __ChooseBulletChildLayer_H__
#include<vector>
#include "SDL_Engine/SDL_Engine.h"
#include "sundry.h"

using namespace SDL;
class BulletCard;
class ChooseBulletChildLayer:public Layer
{
private:
	std::vector<BulletCard*> m_bulletCardVector;
public:
	ChooseBulletChildLayer();
	~ChooseBulletChildLayer();
	CREATE_FUNC(ChooseBulletChildLayer);
	bool init();
public:
	BulletCard*getSelectedItem(const Point&pos);
	BulletCard*getItemByType(BulletType type);
};
#endif