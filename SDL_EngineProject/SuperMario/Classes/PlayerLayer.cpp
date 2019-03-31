#include "PlayerLayer.h"
#include "Player.h"
#include "GameScene.h"

PlayerLayer::PlayerLayer()
	:m_pPlayer(nullptr),m_pDelegate(nullptr)
	,m_pEntityLayer(nullptr)
	,m_bCanJump(false),m_remantHeight(0.f)
	,m_bLeftPressed(false),m_bRightPressed(false)
	,m_bJumpPressed(false),m_bDownPressed(false)
	,m_bShootPressed(false),m_bJumpHigher(false)
{
	m_velocitys[0] = 4.f;
	m_velocitys[1] = 6.f;
	m_velocityPerSec = 0.3f;
	m_jumpHeight[0] = 60;
	m_jumpHeight[1] = 80;
}
PlayerLayer::~PlayerLayer()
{
}
PlayerLayer*PlayerLayer::create(PlayerLayerDelegate*pDelegate)
{
	auto layer = new PlayerLayer();
	if(layer && layer->init(pDelegate))
		layer->autoRelease();
	else
		SDL_SAFE_DELETE(layer);
	return layer;
}
bool PlayerLayer::init(PlayerLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
	//����ʵ���
	m_pEntityLayer = m_pDelegate->getEntityLayer();
	//��������
	m_pPlayer = Player::create();
	m_pEntityLayer->addChild(m_pPlayer);
	//���ó�����
	Point bornPos = m_pDelegate->getPlayerBornPos();
	m_pPlayer->setPosition(bornPos);
	//������������
	m_pPlayer->setMaxHp(3);
	m_pPlayer->setCurHp(1);
	m_pPlayer->setDamage(1);
	m_pPlayer->setBulletNum(2);

	return true;
}
void PlayerLayer::update(float dt)
{
	//�ж������Ƿ��Ѿ�����
	if(m_pPlayer->isDead())
	{
		//todo �������������ļ��
		m_pPlayer->ressurect(1.5f);
		//������������λ��
		m_pPlayer->setPosition(m_lastSafePos);
		return;
	}
	//�����ǰ�����Ѿ��������򲻽��и���
	if(m_pPlayer->isDying())
		return;
	this->updateMarioVelocity(dt);
	//���ǳ���������
	if(this->isPlayerOutside())
	{
		m_pPlayer->hurt(m_pPlayer->getCurHp());
		return;
	}
	auto gravity = m_pDelegate->getGravity();
	auto velocity = m_pPlayer->getVelocity();
/*	if(velocity.y > gravity.y)
		velocity.y = gravity.y;*/
	//�����ٶ�
	if(m_remantHeight > 0)
	{
		velocity.y = -gravity.y;
		m_remantHeight += velocity.y;
	}
	else
	{
		m_remantHeight = 0.f;
		velocity.y = gravity.y;
	}
	bool bLeft = false;
	bool bRight = false;
	bool bJumping = false;
	bool bFalling = false;
	bool bOnLand = false;
	//��ȡ��ײ���
	Rect r = m_pPlayer->getCollisionBoundingBox();
	Point curPos = m_pPlayer->getPosition();
	Point nextVelocity;
	//����x��
	if(velocity.x != 0.f)
	{
		char dir = 0;
		if(velocity.x > 0)
		{
			bRight = true;
			dir = 0x1;
		}
		else 
		{
			bLeft = true;
			dir = 0x2;
		}
		r.origin.x += velocity.x;
		//x���Ϸ�����ײ
		//�Խ�Ҳ�ص�
		m_pDelegate->isCollidedTileWithCoinLayer(r,m_pPlayer,dir);

		if(m_pDelegate->isCollidedTileWithCollidedLayer(r,dir) > 0)
		{
			nextVelocity.x = 0.f;
			//������ײ����ָ�ԭ��״̬
			r.origin.x -= velocity.x;
			velocity.x = 0.f;
		}
		else
		{
			nextVelocity.x = velocity.x;
		}
	}
	//����y��
	r.origin.y += velocity.y;
	char dir = 0;
	if(velocity.y > 0)
		dir = 0x4;
	else
		dir = 0x8;
	//todo
	//�Խ�Ҳ�ص�
	m_pDelegate->isCollidedTileWithCoinLayer(r,m_pPlayer,dir);

	int gid = m_pDelegate->isCollidedTileWithCollidedLayer(r,m_pPlayer,dir);
	//ֻ�д����ϰ����ϲŻ��ܵ�����Ħ����,����x����ٶȲ�Ϊ0
	if(gid > 0)
	{
		//��ײ�����岢���ٶ����£���ʾ���ڵ�����
		if(velocity.y >= 0.f)
		{
			m_bCanJump = true;
			m_bJumpHigher = false;
			bOnLand = true;
			//����Ϊ��ȫ��
			m_lastSafePos = curPos;
		}
		else
		{
			m_remantHeight = 0.f;
		}

		if(velocity.x != 0.f)
		{
			ValueMap properties = m_pDelegate->getTilePropertiesForGID(gid);
			float friction = 0.5;
			if(properties.find("friction") != properties.end())
				friction = properties.at("friction").asFloat();
			//�����෴��Ħ����
			if(velocity.x > 0)
			{
				nextVelocity.x -= friction*m_velocityPerSec;
				if(nextVelocity.x < 0)
					nextVelocity.x = 0;
			}
			else if(velocity.x < 0)
			{
				nextVelocity.x += friction*m_velocityPerSec;
				if(nextVelocity.x > 0)
					nextVelocity.x = 0;
			}
			if(velocity.y < 0)//�����ϰ���
			{
       			bJumping = false;
				bFalling = true;
			}
		}//end if*/
		m_pPlayer->setJumping(false);
		nextVelocity.y = 0.f;
		velocity.y = 0.f;
	}//end gid
	else
	{
		nextVelocity.y = velocity.y;
	}
	auto nextPos = m_pPlayer->getPosition() + velocity;
	m_pPlayer->setPosition(nextPos);
	m_pPlayer->setVelocity(nextVelocity);
	//
	if(velocity.y < 0)
		bJumping = true;
	else if(velocity.y > 0)
		bFalling = true;
	//����״̬
	if(bJumping)
	{
		m_pPlayer->jump();
	}
	else if(bFalling)
	{
		m_pPlayer->fall();
	}
	else if(m_bLeftPressed || m_bRightPressed)
	{
		m_pPlayer->run(bRight);
	}
	else if(m_bDownPressed)
	{
		m_pPlayer->sit();
	}
	else if(bOnLand)
	{
		m_pPlayer->idle();
	}
}
Player*PlayerLayer::getPlayer()const
{
	return m_pPlayer;
}
void PlayerLayer::updateMarioVelocity(float dt)
{
	if(m_bLeftPressed)
		this->playerLeft();
	if(m_bRightPressed)
		this->playerRight();
	if(m_bJumpPressed)
		this->playerJump();
}
void PlayerLayer::keyPressed(EventType type)
{
	if(type == kEventType_Shoot)
	{
		m_bShootPressed = true;
		//���Է����ӵ�
		this->playerShoot();
	}
	if(type == kEventType_Left)
		m_bLeftPressed = true;
	else if(type == kEventType_Right)
		m_bRightPressed = true;
	else if(type == kEventType_Jump)
		m_bJumpPressed = true;
	else if(type == kEventType_Down)
		m_bDownPressed = true;
}
void PlayerLayer::keyReleased(EventType type)
{
	if(type == kEventType_Shoot)
		m_bShootPressed = false;
	if(type == kEventType_Left)
		m_bLeftPressed = false;
	else if(type == kEventType_Right)
		m_bRightPressed = false;
	else if(type == kEventType_Jump)
		m_bJumpPressed = false;
	else if(type == kEventType_Down)
		m_bDownPressed = false;
}
void PlayerLayer::setPlayerRemantHeight(int remantHeight)
{
	m_remantHeight = remantHeight;
}
void PlayerLayer::addPlayerRemantHeight(int remantHeight)
{
	m_remantHeight += remantHeight;
}
void PlayerLayer::playerLeft()
{
	auto velocity = m_pPlayer->getVelocity();
	if(velocity.x <= -m_velocitys[m_bShootPressed])
		velocity.x = -m_velocitys[m_bShootPressed];
	else
		velocity.x -= m_velocityPerSec;
	m_pPlayer->setVelocity(velocity);
}
void PlayerLayer::playerRight()
{
	auto velocity = m_pPlayer->getVelocity();

	if(velocity.x >= SDL_abs(m_velocitys[m_bShootPressed]))
		velocity.x = m_velocitys[m_bShootPressed];
	else
		velocity.x += m_velocityPerSec;
	m_pPlayer->setVelocity(velocity);
}
void PlayerLayer::playerJump()
{
	if(m_bCanJump && m_pPlayer->isJumping() == false)
	{
		m_bCanJump = false;
		m_pPlayer->setJumping(true);
		//����������Ч
		SoundManager::getInstance()->playEffect("sound/mario_jump.ogg",0);
		m_remantHeight += m_jumpHeight[0];
	}
	//������
	if(m_pPlayer->isJumping() == true && m_bJumpHigher == false
		&& (m_lastSafePos.y - m_pPlayer->getPositionY() >= m_jumpHeight[0]))
	{
		m_bJumpHigher = true;
		m_remantHeight += m_jumpHeight[1];
	}/*
	else
	{
		m_pPlayer->setJumping(false);
	}*/
}
void PlayerLayer::playerShoot()
{
	//���жϵ�ǰ�����Ƿ���Է����ӵ�
	if(m_pPlayer->isCanShoot() == false)
		return;
	m_pPlayer->setBulletNum(m_pPlayer->getBulletNum() - 1);
	//��ȡ���ǵ�ǰ����
	bool bRight = m_pPlayer->isDirRight();
	//ȷ���ӵ���ʼλ�ú��ٶȷ���
	Point startPos;
	Point heading = Point(0,1.f);
	Rect r = m_pPlayer->getCollisionBoundingBox();
	if(bRight)
	{
		startPos = Point(r.origin.x + r.size.width,r.origin.y + r.size.height/2);
		heading.x = 1.f;
	}
	else
	{
		startPos = Point(r.origin.x,r.origin.y + r.size.height/2);
		heading.x = -1.f;
	}
	//todo
	m_pDelegate->addPlayerBullet(BulletType::Mario,startPos,heading,to_string(m_pPlayer->getUniqueID()));
}
bool PlayerLayer::isPlayerOutside()
{
	//��ȡ��ǰ����λ��
	auto y = m_pPlayer->getPositionY();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if(y > visibleSize.height)
		return true;
	return false;
}