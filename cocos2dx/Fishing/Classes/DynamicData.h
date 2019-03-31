#ifndef __DynamicData_H__
#define __DynamicData_H__
#include<map>
#include<vector>
#include<string>
#include<cstring>
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class DynamicData:public Ref
{
	CC_SYNTHESIZE(int,m_nAtkAllTimes,AtkAllTimes);//出手总次数
	CC_SYNTHESIZE(int,m_nAtkTimes,AtkTimes);//出手次数
	CC_SYNTHESIZE(int,m_nAnswerTimes,AnswerTimes);//回答问题次数

	CC_SYNTHESIZE(Point,m_offsetRefract,OffsetRefraction);//折射偏移
private:
	static DynamicData*m_pInstance;
	map<int,int> m_needFishes;//关卡需要的鱼的种类以及相应的数量
private:
	DynamicData();
	~DynamicData();
public:
	static DynamicData*getInstance();
	void purge();
	void initlize();
	//清理
	void clean();
	//return 当前步数是否大于0
	bool reduceAtkTimes();//减少出手次数
	void addAtkTimes(int times);//增加出手次数
	//返回是否过关
	bool reduceFish(int id);//减少鱼的相应数量

	map<int,int>& getNeedfulFishes();
	//获得关卡总数目 前提，加载了main.lua
	int getLevelCount()const;
private:
	void initlizeNeedFishes(char*text);
};
#endif