#include "Player.h"
#include "TextureManager.h"

Player::Player()
	:m_textureID(NULL),m_textureMask(NULL)
{
}
Player::~Player()
{
}
BOOL Player::load(LPCWSTR textureID,LPCWSTR textureMask)
{
	m_textureID = textureID;
	m_textureMask = textureMask;
	//初始化角色
	m_size.cx = 640/5;
	m_size.cy = 55;
	//初始化位置
	RECT r = TextureManager::getInstance()->getClientRect();
	m_position.x = r.right - r.left - m_size.cx;
	m_position.y = (r.bottom - r.top)/2;

	return TRUE;
}
void Player::draw()
{
	//绘制
	//先绘制蒙版
	TextureManager::getInstance()->bitBlt(m_textureMask,
		0,0,
		m_size.cx,m_size.cy,
		0,0,SRCAND);
}
void Player::update()
{
}
void Player::clean()
{
}