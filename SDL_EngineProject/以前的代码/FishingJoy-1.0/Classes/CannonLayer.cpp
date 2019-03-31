#include "CannonLayer.h"
#include "Weapon.h"
CannonLayer::CannonLayer()
	:m_pWeapon(nullptr),m_pBackground(nullptr)
{
}
CannonLayer::~CannonLayer()
{
}
bool CannonLayer::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//添加背景tab
	m_pBackground = Sprite::createWithSpriteFrameName("ui_end.png");
	m_pBackground->setPositionY(visibleSize.height-m_pBackground->getContentSize().height);
	this->addChild(m_pBackground,-1);

	m_pWeapon = Weapon::create();
	Size weaponSize = m_pWeapon->getContentSize();
	//武器居中
	m_pWeapon->setPosition((visibleSize.width-weaponSize.width)/2,visibleSize.height-weaponSize.height-10);
	this->addChild(m_pWeapon);

	//添加按钮 来改变武器 等级
	auto buttonAdd = MenuItemSprite::create(
		Sprite::createWithSpriteFrameName("btn_add_normal.png")
		,Sprite::createWithSpriteFrameName("btn_add_selected.png")
		,nullptr,SDL_CALLBACK_1(CannonLayer::addWeaponLevel,this));
	Size btnSize = buttonAdd->getContentSize();
	buttonAdd->setPosition((visibleSize.width-weaponSize.width)/2+weaponSize.width,visibleSize.height-btnSize.height);
	auto buttonSub = MenuItemSprite::create(
		Sprite::createWithSpriteFrameName("btn_sub_normal.png")
		,Sprite::createWithSpriteFrameName("btn_sub_selected.png")
		,nullptr,SDL_CALLBACK_1(CannonLayer::subWeaponLevel,this));
	buttonSub->setPosition((visibleSize.width-weaponSize.width)/2-weaponSize.width,visibleSize.height-btnSize.height);
	Menu*menu = Menu::create(buttonAdd,buttonSub,nullptr);
	this->addChild(menu);
	return true;
}
void CannonLayer::aimAt(const Point&target)
{
	m_pWeapon->aimAt(target);
}
void CannonLayer::shootTo(const Point&target)
{
	Rect rect;
	rect.origin = m_pBackground->getWorldPosition();
	rect.size = m_pBackground->getContentSize();
	//如果没有点击海面，则坐标不向下传入
	if(!rect.containsPoint(target))
		m_pWeapon->shootTo(target);
}
Weapon*CannonLayer::getWeapon()const
{
	return m_pWeapon;
}
void CannonLayer::addWeaponLevel(Object*)
{
	SoundManager::getInstance()->playEffect("sound_button.mp3",0);
	m_pWeapon->addCannonLevel();
}
void CannonLayer::subWeaponLevel(Object*)
{
	SoundManager::getInstance()->playEffect("sound_button.mp3",0);
	m_pWeapon->subCannonLevel();
}