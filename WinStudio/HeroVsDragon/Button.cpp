#include "Button.h"
#include "TextureManager.h"
#include "Skill.h"

Button::Button()
	:m_pNormalID(NULL)
	,m_bShowDetail(false),m_pSkill(NULL)
{
}
Button::~Button()
{
}
bool Button::load(int x,int y,int w,int h,LPCWSTR textureID)
{
	m_pNormalID = textureID;
	m_rect.left = x;
	m_rect.right = x + w;
	m_rect.top = y;
	m_rect.bottom = y + h;
	//加载资源
	return TextureManager::getInstance()->load(textureID,textureID);
}
void Button::draw(HDC hdc)
{
	TextureManager::getInstance()->bitBlt(m_pNormalID,
		m_rect.left,m_rect.top,
		m_rect.right - m_rect.left,m_rect.bottom - m_rect.top
		,0,0,SRCCOPY);
	//显示技能详细
	if(m_bShowDetail)
	{
		auto skillName = m_pSkill->getName();
		auto skillDesc = m_pSkill->getDesc();
		//
		TEXTMETRIC tm;
		TextureManager::getInstance()->getTextMetrics(&tm);
		RECT rect = {0,tm.tmHeight,100,200};

		TextureManager::getInstance()->textOut(0,0,skillName,wcslen(skillName),RGB(255,255,255));
		//开启左对齐和自动换行
		TextureManager::getInstance()->drawText(skillDesc,wcslen(skillDesc),&rect,DT_LEFT|DT_WORDBREAK,RGB(0,0,0));
		//TextureManager::getInstance()->textOut(0,tm.tmHeight,skillDesc,wcslen(skillDesc),RGB(0,0,0));
	}
}
void Button::update()
{
}
void Button::clean()
{
}
void Button::bindSkill(Skill*pSkill)
{
	m_pSkill = pSkill;
}
void Button::mouseMove(DWORD x,DWORD y)
{
	if(x >= m_rect.left && x <= m_rect.right
		&& y >= m_rect.top && y<= m_rect.bottom)
		m_bShowDetail = true;
	else
		m_bShowDetail = false;
}
void Button::mouseLBDown(DWORD x,DWORD y)
{
}