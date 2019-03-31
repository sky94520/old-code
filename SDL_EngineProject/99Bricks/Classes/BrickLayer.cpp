#include "BrickLayer.h"
#include "Brick.h"

BrickLayer::BrickLayer()
{
}
BrickLayer::~BrickLayer()
{
}
bool BrickLayer::init()
{
	//m_bricks=
	bool z[9] = {1,1,0,0,1,1,0,0,0};
	//m_bricks.push_back(z);

	//���ɷ���
	Brick*brick = this->createBrick(z);
	this->addChild(brick);
	
	return true;
}

Brick*BrickLayer::createBrick(bool arrays[9])
{
	//bool z[9] = {1,1,0,0,1,1,0,0,0};
	Size visibleSize = Director::getInstance()->getVisibleSize();
	float length = 1.f;//
	int PTM_RATIO = PhysicalEngine::getInstance()->PTM_RATIO;;
	//����body,������λ��
	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2(visibleSize.width/PTM_RATIO/2,0);
	bodyDef.type = b2_dynamicBody;
	b2Body*body = PhysicalEngine::getInstance()->createBody(&bodyDef);
	b2PolygonShape shape;

	for(int row=0;row < 3;row++)
	{
		for(int col=0;col<3;col++)
		{
			if(arrays[row*3 + col] == true)
			{
				float x = col*length;
				float y = row*length;
				//������״
				shape.SetAsBox(length/2,length/2,b2Vec2(0.5f + x,0.5f + y),0);
				body->CreateFixture(&shape,1.f);
			}
		}
	}
	body->ResetMassData();
	//���������ٶ�
	body->SetLinearVelocity(b2Vec2(0,2.f));
	body->SetLinearDamping(0);
	Brick*brick = Brick::create(body);
	return brick;
}