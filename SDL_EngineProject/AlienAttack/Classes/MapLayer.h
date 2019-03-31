#ifndef __MapLayer_H__
#define __MapLayer_H__
#include<string>
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
using namespace std;
class Player;
/*����1.���ص�ͼ 2.��ͼ����*/
class MapLayer:public Layer
{
	SDL_SYNTHESIZE(float,m_scrollSpeed,ScrollSpeed);//��ͼ�����ٶ�
private:
	TMXTiledMap*m_pTiledMap;
	Sprite*m_pBg1;
	Sprite*m_pBg2;
public:
	MapLayer();
	~MapLayer();
	static MapLayer*create(const string&level);

	bool init(const string&level);
	virtual void update(float dt);
	//�����������ײ���Ƿ���ײ
	void checkCollisionBetweenPlayerAndMap(Player*player);

	std::vector<TMXObject*> getTMXObjects();
	void reset();
	void clear();
};
#endif