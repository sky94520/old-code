#ifndef __DynamicData_H__
#define __DynamicData_H__
#include<vector>
#include<algorithm>
#include "PlatformMarcos.h"
class Item;
using namespace std;
class DynamicData
{
	SDL_SYNTHESIZE(int,m_nGold,Gold);//���
private:
	vector<Item*> m_packages;//����
	static DynamicData*m_pInstance;
private:
	DynamicData();
	~DynamicData();
public:
	static DynamicData*getInstance();
	void purge();//�ͷŵ�ǰ������

	int sellItem(Item*pItem);//���۵���
	void alertGold(int gold); //�޸Ľ�Ǯ
	vector<Item*>*getPackages();//��õ�ǰ��������
};
#endif