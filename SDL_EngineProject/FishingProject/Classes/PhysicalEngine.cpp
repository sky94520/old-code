#include "PhysicalEngine.h"
#include "GLES-Render.h"
#include "Entity.h"
#include "Fish.h"
#include "Fork.h"

PhysicalEngine*PhysicalEngine::m_pInstance = nullptr;
const int PhysicalEngine::PTM_RATIO = 32;

PhysicalEngine::PhysicalEngine()
	:m_pWorld(nullptr),m_pDebugDraw(nullptr)
{
}
PhysicalEngine::~PhysicalEngine()
{
}
PhysicalEngine*PhysicalEngine::getInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new PhysicalEngine();
		m_pInstance->init();
	}
	return m_pInstance;
}
void PhysicalEngine::purge()
{
	CC_SAFE_DELETE(m_pInstance);
}
bool PhysicalEngine::init()
{
	//������������
	b2Vec2 gravity(0.f,0.f);
	m_pWorld = new b2World(gravity);
	m_pWorld->SetAllowSleeping(true);//��������
	m_pWorld->SetContinuousPhysics(true);//�����������
	//m_pWorld->SetContactListener(this);//���ü�����
	//��������
	m_pDebugDraw = new GLESDebugDraw(PTM_RATIO);
	m_pWorld->SetDebugDraw(m_pDebugDraw);
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	/*flags += b2Draw::e_jointBit;
	flags += b2Draw::e_aabbBit;
	flags += b2Draw::e_pairBit;
	flags += b2Draw::e_centerOfMassBit;*/

	m_pDebugDraw->SetFlags(flags);
	return true;
}
void PhysicalEngine::update(float time)
{
	float32 timeStep = 1.f/60;//ʱ�䲽
	int32 velocityIterations = 6;//�ٶȵ�������
	int32 positionIterations = 2;//λ�õ�������

	for(b2Body*b = m_pWorld->GetBodyList();b;b = b->GetNext())
	{
		//���ʹ��������˶�
		if(b->GetUserData())
		{
			Entity*entity = static_cast<Entity*>(b->GetUserData());
			Sprite*sprite = entity->getSprite();
			b2Vec2 b2Position = b2Vec2(entity->getPositionX()/PTM_RATIO,entity->getPositionY()/PTM_RATIO);
			float32 b2Angle = - CC_DEGREES_TO_RADIANS(sprite->getRotationX());

			b->SetTransform(b2Position,b2Angle);
		}
	}
	m_pWorld->Step(timeStep,velocityIterations,positionIterations);
}
void PhysicalEngine::SetContactListener(b2ContactListener*listener)
{
	m_pWorld->SetContactListener(listener);
}
void PhysicalEngine::bindBodyForFish(Fish*pFish)
{
	Size size = pFish->getColliableRect().size;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	//��������
	b2Body*body = m_pWorld->CreateBody(&bodyDef);
	//��״
	/*b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(size.width/PTM_RATIO/2,size.height/PTM_RATIO/2);*/
	b2CircleShape dynamicBox;
	dynamicBox.m_radius = size.width/PTM_RATIO/2;
	//�����о�
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	//����ܶ�Ϊ1.0f 
	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.3f;
	//��������־λ
	fixtureDef.filter.categoryBits = 0x01;
	//������ײ��־λ
	fixtureDef.filter.maskBits = 0x04;
	//�󶨼о�
	body->CreateFixture(&fixtureDef);
	body->SetUserData(pFish);
}
void PhysicalEngine::bindScaredBodyForFish(Fish*pFish)
{
	Size size = pFish->getScaredRect().size;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	//��������
	b2Body*body = m_pWorld->CreateBody(&bodyDef);
	//��״
	b2CircleShape dynamicBox;
	dynamicBox.m_radius = size.width/PTM_RATIO/2;
	//b2PolygonShape dynamicBox;
	//dynamicBox.SetAsBox(size.width/PTM_RATIO/2,size.height/PTM_RATIO/2);
	//�����о�
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.3f;
	//��������־λ
	fixtureDef.filter.categoryBits = 0x02;
	//������ײ��־λ
	fixtureDef.filter.maskBits = 0x04;
	//�󶨼о�
	body->CreateFixture(&fixtureDef);
	body->SetUserData(pFish);
}
void PhysicalEngine::bindBodyForFork(Fork*pFork)
{
	vector<Rect>&rects = pFork->getColliableRects();
	auto rect = rects.at(0);
	Size size = rect.size;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	//��������
	b2Body*body = m_pWorld->CreateBody(&bodyDef);
	//��״
	b2CircleShape dynamicBox;
	dynamicBox.m_radius = size.width/PTM_RATIO/2;
	//b2PolygonShape dynamicBox;
	//dynamicBox.SetAsBox(size.width/PTM_RATIO/2,size.height/PTM_RATIO/2);
	//�����о�
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.3f;
	//��������־λ
	fixtureDef.filter.categoryBits = 0x04;
	//������ײ��־λ
	fixtureDef.filter.maskBits = 0x03;
	//�󶨼о�
	body->CreateFixture(&fixtureDef);
	body->SetUserData(pFork);
}
void PhysicalEngine::draw(const Mat4 &transform, uint32_t flags)
{
	kmGLPushMatrix();
	kmGLLoadMatrix(&transform);
	m_pWorld->DrawDebugData();
	kmGLPopMatrix();
}