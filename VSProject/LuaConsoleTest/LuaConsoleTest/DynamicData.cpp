#include "DynamicData.h"
#include "UserDefault.h"
#include "StringUtils.h"
#include "Item.h"
#include "Weapon.h"
DynamicData*DynamicData::m_pInstance = nullptr;
DynamicData::DynamicData()
	:m_nGold(0)
{
	//��ȡ�����ļ�
	//��ȡ���
	m_nGold = UserDefault::getInstance()->getIntegerForKey("gold",50);
	//������
	std::string str = UserDefault::getInstance()->getStringForKey("packages","0 Heirloom");
	auto valueVector = StringUtils::split(str,",");
	for(int i=0;i < valueVector.size();i++)
	{
		auto tempVec = StringUtils::split(valueVector.at(i).asString()," ");
		auto type = tempVec.at(0).asInt();
		auto stringID = tempVec.at(1).asString();
		Item*item = nullptr;
		switch(type)
		{
		case ItemType::kItemType_Weapon: item = new Weapon();item->init(stringID);
			break;
		}
		m_packages.push_back(item);
	}
}
DynamicData::~DynamicData()
{
	//������
	UserDefault::getInstance()->setIntegerForKey("gold",m_nGold);
	//���汳��
	std::stringstream strstream;
	for(int i=0;i<m_packages.size();i++)
	{
		auto item = m_packages.at(i);
		strstream<<item->getItemType()<<" "<<m_packages.at(i)->getStringID()<<",";
	}
	//ȥ�����һ������
	auto str = strstream.str();
	str = str.substr(0,str.length() - 1);
	//����װ��
	UserDefault::getInstance()->setStringForKey("packages",str);
}
DynamicData*DynamicData::getInstance()
{
	if(m_pInstance == nullptr)
		m_pInstance = new DynamicData();
	return m_pInstance;
}
void DynamicData::purge()
{
	SDL_SAFE_DELETE(m_pInstance);
}
int DynamicData::sellItem(Item*pItem)
{
	int price = pItem->getPrice();
	m_nGold += price;
	//ɾ���õ���
	//ȥ����װ��
	auto iter = std::find_if(m_packages.begin(),m_packages.end(),[pItem](Item*item)
	{
		return pItem == item;
	});
	m_packages.erase(iter);
	delete pItem;
	return price;
}
void DynamicData::alertGold(int gold)
{
	m_nGold += gold;
}
vector<Item*>* DynamicData::getPackages()
{
	return &m_packages;
}