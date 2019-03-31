#include "MapLayer.h"
#include "Brick.h"

MapLayer::MapLayer()
	:m_mapSize(10,20)
{
	auto size = sizeof(m_pMap);
	memset(m_pMap,0,sizeof(m_pMap));
}
MapLayer::~MapLayer()
{
}
bool MapLayer::init()
{
	//���ñ߽� ����߽�
	for(int i=0;i<m_mapSize.width+2;i++)
	{
		Sprite*sprite = Sprite::createWithSpriteFrameName("block.png");
		Size s = sprite->getContentSize();
		Point pos = Point(i*s.width,m_mapSize.height*s.height);
		sprite->setPosition(pos);
		sprite->setTag(1);
		sprite->setAnchorPoint(Point(0,0));

		this->addChild(sprite);
		m_pMap[20][i] = sprite;
	}
	//����߽�
	for(int i=0;i<m_mapSize.height;i++)
	{
		//��
		Sprite*sprite = Sprite::createWithSpriteFrameName("block.png");
		Size s = sprite->getContentSize();

		Point pos = Point((m_mapSize.width+1)*s.height,i*s.width); 
		sprite->setPosition(pos);
		sprite->setAnchorPoint(Point(0,0));
		sprite->setTag(1);

		this->addChild(sprite);
		m_pMap[i][11] = sprite;
		//��
		Sprite*s2 = Sprite::createWithSpriteFrameName("block.png");
		Point pos2 = Point(0,i*s.width);
		s2->setPosition(pos2);
		s2->setAnchorPoint(Point(0.f,0.f));
		s2->setTag(1);
		this->addChild(s2);
		m_pMap[i][0] = s2;
	}
	Sprite*sprite = Sprite::createWithSpriteFrameName("block.png");
	Size s = sprite->getContentSize();
	//���ÿͻ��� ��С
	m_clientRect.origin = Point(s.width,s.height);
	m_clientRect.size = Size(m_mapSize.width*s.width,m_mapSize.height*s.height);
	//���÷����С
	m_tileSize = s;
	return true;
}
void MapLayer::update(float dt)
{
	Renderer*renderer = Director::getInstance()->getRenderer();
	const Rect rect = this->getClientRect();
	const Size size = this->getTileSize();
	for(int i=1;i<10;i++)
	{
		Point startPos = Point(rect.origin.x + size.width*i,0);
		Point endPos = startPos + Point(0,rect.size.height);
		//��ȡԭ�ȵ���Ⱦģʽ
		SDL_BlendMode oldMode = SDL_BLENDMODE_NONE;
		auto renderer = Director::getInstance()->getRenderer();
		renderer->getRenderDrawBlendMode(&oldMode);
		Color oldColor = renderer->getRenderDrawColor();
		::aalineRGBA(renderer->getSDL_Renderer(),startPos.x,startPos.y,endPos.x,endPos.y,0,0,0,128);
		renderer->setRenderDrawBlendMode(oldMode);
		renderer->setRenderDrawColor(oldColor.r,oldColor.g,oldColor.b,oldColor.a);
	}
}
bool MapLayer::isCollided(Brick*brick)
{
	Shape&shape = brick->getShape();
	Point brickPos = brick->getPosition();

	for(int i=0;i<4;i++)
	{
		//ת��Ϊmap����
		int x = brickPos.x/m_tileSize.width + shape.p[i].x;
		int y = brickPos.y/m_tileSize.height + shape.p[i].y;
		//�������
		if(x <= 0 || x >= 11)
			return true;
		//�����ڵ�ͼ�⣬�������ײ
		if(x < 0 || y < 0)
		{
			continue;
		}
		//�Ƿ�����ײ
		if(m_pMap[y][x])
		{
			return true;
		}
	}
	return false;
}
/*
���жϵ�ǰλ���Ƿ�����Ļ�⣬Ȼ���ټ�һ��������0�����ж���һ���Ƿ�ᷢ����ײ
*/
CollideResult MapLayer::isGameOver(Brick*brick)
{
	Shape&shape = brick->getShape();
	Point brickPos = brick->getPosition();
	bool bColliede = false;
	//�ڷ�����ײʱ���з����ڵ�ͼ�⣬��Ϸ����
	bool bOutside = false;
	//ת��Ϊmap����
	for(int i=0;i<4;i++)
	{
		int x = brickPos.x/m_tileSize.width + shape.p[i].x;
		int y = brickPos.y/m_tileSize.height + shape.p[i].y;
		//�����ڵ�ͼ�⣬�������ײ���п��ܽ�����Ϸ
		if(x < 0)
		{
			bOutside = true;
			continue;
		}
		if(y < 0)
		{
			bOutside = true;
		}
		y++;
		if(y < 0)
			continue;
		//�Ƿ�����ײ
		if(m_pMap[y][x])
		{
			bColliede = true;
		}
	}
	//��Ϸ����
	if(bColliede && bOutside)
		return kResult_GameOver;
	if(bColliede)
		return kResult_OnlyCollided;
	return kResult_None;
}
/*ֻҪ�ǲ��룬��һ���ǺϷ��ģ��������yֵ>0*/
void MapLayer::insertBrick(Brick*brick)
{
	Shape&shape = brick->getShape();
	Point brickPos = brick->getPosition();
	auto spriteName = brick->getSpriteName();

	for(int i=0;i<4;i++)
	{
		int x = brickPos.x/m_tileSize.width + shape.p[i].x;
		//�������һ
		int y = brickPos.y/m_tileSize.height + shape.p[i].y;
		
		Sprite*sprite = Sprite::createWithSpriteFrameName(spriteName);
		sprite->setPosition(x*m_tileSize.width,y*m_tileSize.height);
		sprite->setAnchorPoint(Point(0.f,0.f));
		m_pMap[y][x] = sprite;
		this->addChild(sprite);
	}
}
int MapLayer::clearUpBrick()
{
	int counts = 0;
	for(int i=19;i >= 0;)
	{
		bool bCleared = true;
		for(int j=1;j < 11;j++)
		{
			if(m_pMap[i][j] == nullptr)
			{
				bCleared = false;
				break;
			}
		}
		//�����������������
		if(bCleared == false)
		{
			--i;
			continue;
		}
		//��������������
		counts ++;
		Sprite* tempMap[10];
		for(int temp=0;temp<10;temp++)
			tempMap[temp] = m_pMap[i][temp+1];

		bool bExited = false;
		for(int m=i;m > 0 && !bExited;m--)
		{
			bExited = true;
			for(int n=1;n < 11;n++)
			{
				Sprite*sprite = m_pMap[m-1][n];
				
				bExited = false;
				m_pMap[m][n] = sprite;
				if(sprite)
					sprite->setPosition(Point(m_tileSize.width*n,m_tileSize.height*m));
			}
		}
		//�������
		for(int k = 0;k < 10;k++)
		{
			Sprite*s = tempMap[k];
			s->removeFromParent();
		}
	}
	return counts;
}
void MapLayer::reset()
{
	//�������
	for(int i=19;i >= 0;i--)
	{
		bool bCleared = true;
		for(int j=1;j < 11;j++)
		{
			auto sprite = m_pMap[i][j];
			if(sprite)
			{
				this->removeChild(sprite);
				m_pMap[i][j] = nullptr;
			}
		}
	}
}