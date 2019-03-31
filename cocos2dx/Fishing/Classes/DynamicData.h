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
	CC_SYNTHESIZE(int,m_nAtkAllTimes,AtkAllTimes);//�����ܴ���
	CC_SYNTHESIZE(int,m_nAtkTimes,AtkTimes);//���ִ���
	CC_SYNTHESIZE(int,m_nAnswerTimes,AnswerTimes);//�ش��������

	CC_SYNTHESIZE(Point,m_offsetRefract,OffsetRefraction);//����ƫ��
private:
	static DynamicData*m_pInstance;
	map<int,int> m_needFishes;//�ؿ���Ҫ����������Լ���Ӧ������
private:
	DynamicData();
	~DynamicData();
public:
	static DynamicData*getInstance();
	void purge();
	void initlize();
	//����
	void clean();
	//return ��ǰ�����Ƿ����0
	bool reduceAtkTimes();//���ٳ��ִ���
	void addAtkTimes(int times);//���ӳ��ִ���
	//�����Ƿ����
	bool reduceFish(int id);//���������Ӧ����

	map<int,int>& getNeedfulFishes();
	//��ùؿ�����Ŀ ǰ�ᣬ������main.lua
	int getLevelCount()const;
private:
	void initlizeNeedFishes(char*text);
};
#endif