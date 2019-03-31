#include "BackgroundLayer.h"
#include "TextureManager.h"

BackgroundLayer::BackgroundLayer()
	:m_textureID(NULL)
{
	memset(&m_pos1,0,sizeof(POINT));
	memset(&m_pos2,0,sizeof(POINT));
}
BackgroundLayer::~BackgroundLayer()
{
}
BOOL BackgroundLayer::load(LPCWSTR textureID)
{
	//获取屏幕大小
	RECT rect = TextureManager::getInstance()->getClientRect();
	m_pos2.x = rect.right - rect.left;
	//加载
	m_textureID = textureID;
	return TextureManager::getInstance()->load(textureID,textureID);
}
void BackgroundLayer::draw()
{
	//渲染两次，确保背景移动
	TextureManager::getInstance()->bitBlt(m_textureID,
		m_pos1.x,m_pos1.y,
		800,600,
		0,0,
		SRCCOPY);
	TextureManager::getInstance()->bitBlt(m_textureID,
		m_pos2.x,m_pos2.y,
		800,600,
		0,0,
		SRCCOPY);
}
void BackgroundLayer::update()
{
	RECT r = TextureManager::getInstance()->getClientRect();
	auto width = r.right - r.left;
	m_pos1.x-=5;
	m_pos2.x-=5;
	if(m_pos1.x <= -width)
		m_pos1.x = width;
	if(m_pos2.x <= -width)
		m_pos2.x = width;
}
void BackgroundLayer::clean()
{
}