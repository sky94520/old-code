#include "HelloWorldScene.h"
HelloWorld::HelloWorld()
	:world(nullptr)
{
}
HelloWorld::~HelloWorld()
{
	CC_SAFE_DELETE(world);
}
Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    //�����������
	initPhysics();
	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	scheduleUpdate();
	Sprite*sprite = Sprite::create("CloseNormal.png");
	sprite->setPosition(400,400);
	sprite->setRotation(50);
	this->addChild(sprite);
	//������̬����
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.angle = 50.f;
	bodyDef.position.Set(400.f/PTM_RATIO,400.f/PTM_RATIO);
	b2Body*body = world->CreateBody(&bodyDef);
	body->SetUserData(sprite);

	b2PolygonShape shape;
	Size s = sprite->getContentSize()/PTM_RATIO/2;
	shape.SetAsBox(s.width,s.height);
	body->CreateFixture(&shape,1.f);
    return true;
}
void HelloWorld::update(float dt)
{
	float timestep = 0.03f;
	int32 velocityIterations = 8;
	int32 positionIterations =1;
	world->Step(timestep,velocityIterations,positionIterations);
	for(b2Body*body = world->GetBodyList();body;body = body->GetNext())
	{
		if(body->GetUserData() != nullptr)
		{
			Sprite*sprite = (Sprite*)body->GetUserData();
			sprite->setPosition(ccp(body->GetPosition().x*PTM_RATIO,body->GetPosition().y*PTM_RATIO));
			sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(body->GetAngle()));
		}
	}
}
void HelloWorld::initPhysics()
{
	auto size = Director::getInstance()->getVisibleSize();
	//����
	b2Vec2 gravity;
	gravity.Set(0,0);

	world = new b2World(gravity);
	world->SetAllowSleeping(true);
	world->SetContinuousPhysics(true);
	world->SetContactListener(this);
	//���õ���
	m_debugDraw = new GLESDebugDraw(PTM_RATIO);
	world->SetDebugDraw(m_debugDraw);
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	m_debugDraw->SetFlags(flags);
	//���涨��
	b2BodyDef groundDef;
	groundDef.position.Set(0,0);
	//������������
	b2Body*body = world->CreateBody(&groundDef);
	//����һ����״
	b2EdgeShape groundBox;
	//�ײ�
	groundBox.Set(b2Vec2(0,0),b2Vec2(size.width/PTM_RATIO,0));
	//�̶�������
	body->CreateFixture(&groundBox,0);
	//����
	groundBox.Set(b2Vec2(0,size.height/PTM_RATIO),b2Vec2(size.width/PTM_RATIO,size.height/PTM_RATIO));
	body->CreateFixture(&groundBox,0);
	//���
	groundBox.Set(b2Vec2(0,0),b2Vec2(0,size.height/PTM_RATIO));
	body->CreateFixture(&groundBox,0);
	//�ұ�
	groundBox.Set(b2Vec2(size.width/PTM_RATIO,0),
		b2Vec2(size.width/PTM_RATIO,size.height/PTM_RATIO));
	body->CreateFixture(&groundBox,0);
}
void HelloWorld::BeginContact(b2Contact* contact)
{
	b2Body*bodyA = contact->GetFixtureA()->GetBody();
	b2Body*bodyB = contact->GetFixtureB()->GetBody();
	auto spriteA = (Sprite*)bodyA->GetUserData();
	auto spriteB = (Sprite*)bodyB->GetUserData();
	if(spriteA && spriteB)
	{
		spriteA->setColor(Color3B::RED);
		spriteB->setColor(Color3B::RED);
	}
}
void HelloWorld::EndContact(b2Contact* contact)
{
	b2Body*bodyA = contact->GetFixtureA()->GetBody();
	b2Body*bodyB = contact->GetFixtureB()->GetBody();
	auto spriteA = (Sprite*)bodyA->GetUserData();
	auto spriteB = (Sprite*)bodyB->GetUserData();
	if(spriteA && spriteB)
	{
		spriteA->setColor(Color3B::WHITE);
		spriteB->setColor(Color3B::WHITE);
	}
}
bool HelloWorld::onTouchBegan(Touch*touch,Event*event)
{
	auto pos = Director::getInstance()->convertToGL(touch->getLocationInView());
	addNewSpriteAtPosition(pos);
	return true;
}
void HelloWorld::onDraw(const kmMat4 &transform,bool transformUpdated)
{
	kmGLPushMatrix();
	kmGLLoadMatrix(&transform);
	world->DrawDebugData();
	//��������
	kmGLPopMatrix();
}
void HelloWorld::draw(Renderer*renderer,const kmMat4 &transform,uint32_t flags)
{
	_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(HelloWorld::onDraw,this,transform,flags);
	renderer->addCommand(&_customCommand);
}
void HelloWorld::addNewSpriteAtPosition(Vec2 pos)
{
	Sprite*sprite = Sprite::create("bullet_01.png");
	sprite->setPosition(pos);
	this->addChild(sprite);
	//���嶨��
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x/PTM_RATIO,pos.y/PTM_RATIO);
	
	b2Body*body = world->CreateBody(&bodyDef);
	body->SetUserData(sprite);
	//������״
	b2CircleShape dynamicBox;
	Size s = sprite->getContentSize()/PTM_RATIO;
	dynamicBox.m_radius = s.width/2;
	Vec2 point = sprite->getPosition()/PTM_RATIO;
	//dynamicBox.m_p = b2Vec2(point.x,point.y);
	//�о�
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	//�ܶ�
	fixtureDef.density = 1.f;
	//Ħ��ϵ��
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);

}