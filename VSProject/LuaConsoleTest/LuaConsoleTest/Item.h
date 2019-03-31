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
	SDL_SYNTHESIZE(std::string,m_name,Name);//����
	SDL_SYNTHESIZE(std::string,m_description,Description);//����
	SDL_SYNTHESIZE(int,m_nPrice,Price);//����۸񣬳��ۼ۸�Ϊ����۸��һ��
	SDL_SYNTHESIZE(ItemType,m_itemType,ItemType);
public:
	Item():
		m_stringID(""),m_name(""),m_description(""),m_nPrice(0),m_itemType(ItemType::kItemType_Weapon){}
	/*���崦������Ʒʹ�ú�ֱ��delete��������������Ķ�*/
	virtual void use() = 0;
	virtual bool init(const std::string&stringID)=0;
	virtual std::string toString()const=0;
};
#endif