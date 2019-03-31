#include "Monster.h"
#include "TextureManager.h"

Monster::Monster()
{
}
Monster::~Monster()
{
}
BOOL Monster::load(int x,int y,int w,int h,LPCWSTR textureID)
{
	m_position.x = x;
	m_position.y = y;

	m_size.cx = w;
	m_size.cy = h;

	m_textureID = textureID;
	return TextureManager::getInstance()->load(textureID,textureID);
}
void Monster::draw(HDC hdc)
{
	TextureManager::getInstance()->transparentBlt(m_textureID,
		m_position.x,m_position.y,
		m_size.cx,m_size.cy,
		0,0,m_size.cx,m_size.cy,RGB(0,0,0));
	//显示人物当前信息 hp
	TCHAR text1[20];
	TCHAR text2[20];
	swprintf(text1,20,L"HP:%d/%d",m_nNowHp,m_nMaxHp);
	swprintf(text2,20,L"MP:%d/%d",m_nNowMp,m_nMaxMp);

	POINT pos = {m_position.x + m_size.cx/2,m_position.y};
	TextureManager::getInstance()->textOut(pos.x,pos.y,
		text1,wcslen(text1),RGB(255,0,0));
	//人物mp 
	TextureManager::getInstance()->textOut(pos.x,pos.y + 20,text2,wcslen(text2),RGB(0,0,255));
}
void Monster::update()
{
}
void Monster::clean()
{
}