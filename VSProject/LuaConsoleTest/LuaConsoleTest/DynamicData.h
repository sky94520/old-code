#ifndef __DynamicData_H__
#define __DynamicData_H__
#include<vector>
#include<algorithm>
#include "PlatformMarcos.h"
class Item;
using namespace std;
class DynamicData
{
	SDL_SYNTHESIZE(int,m_nGold,Gold);//金币
private:
	vector<Item*> m_packages;//背包
	static DynamicData*m_pInstance;
private:
	DynamicData();
	~DynamicData();
public:
	static DynamicData*getInstance();
	void purge();//释放当前单例类

	int sellItem(Item*pItem);//出售道具
	void alertGold(int gold); //修改金钱
	vector<Item*>*getPackages();//获得当前背包内容
};
#endif