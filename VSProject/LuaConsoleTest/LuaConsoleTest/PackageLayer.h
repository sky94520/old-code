#ifndef __PackageLayer_H__
#define __PackageLayer_H__
#include<vector>
#include<iostream>
#include<cmath>
class Item;
class Player;
using namespace std;
class PackageLayerDelegate
{
public:
	virtual ~PackageLayerDelegate(){}
	virtual bool use(Item*pItem)=0;
	virtual int sell(Item*pItem)=0;
};
class PackageLayer
{
private:
	PackageLayerDelegate*m_pDelegate;
public:
	PackageLayer();
	~PackageLayer();
	bool init();

	void show();

	void setDelegate(PackageLayerDelegate*pDelegate);
};
#endif