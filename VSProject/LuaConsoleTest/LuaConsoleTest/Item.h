#ifndef __Item_H__
#define __Item_H__
#include<string>
#include "PlatformMarcos.h"
enum ItemType
{
	kItemType_Weapon/*,
	kItemType_Depletion*/
};
class Item
{
	SDL_SYNTHESIZE(std::string,m_stringID,StringID);//String ID
	SDL_SYNTHESIZE(std::string,m_name,Name);//名称
	SDL_SYNTHESIZE(std::string,m_description,Description);//描述
	SDL_SYNTHESIZE(int,m_nPrice,Price);//买入价格，出售价格为买入价格的一半
	SDL_SYNTHESIZE(ItemType,m_itemType,ItemType);
public:
	Item():
		m_stringID(""),m_name(""),m_description(""),m_nPrice(0),m_itemType(ItemType::kItemType_Weapon){}
	/*具体处理，消耗品使用后直接delete，武器则减少消耗度*/
	virtual void use() = 0;
	virtual bool init(const std::string&stringID)=0;
	virtual std::string toString()const=0;
};
#endif