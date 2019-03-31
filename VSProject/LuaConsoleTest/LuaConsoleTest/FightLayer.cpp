#include "FightLayer.h"
#include "Player.h"
#include "Monster.h"
#include "GlobalFunctions.h"
#include "DynamicData.h"
FightLayer::FightLayer()
{
}
FightLayer::~FightLayer()
{
}
void FightLayer::fight(Player*pPlayer,std::vector<Monster*>*pMonsters)
{
	int key = 0;
	bool quit = false;
	int time = 1;//当前的轮数
	//获取将要出现的怪物
	//以及打死之后将会获得的奖励
	std::vector<Monster*> monsters;
	for(int i=0;i<pMonsters->size();i++)
	{
		auto monster = pMonsters->at(i);
		if(monster->isDead() == false)
			monsters.push_back(monster);
	}
	while(!quit)
	{
		quit = true;
		system("cls");
		cout<<"-----------------------第"<<time++<<"轮--------------------"<<endl;
		for(int i=0;i<monsters.size() && !monsters.at(i)->isDead();i++)
		{
			cout<<"敌人"<<i+1<<endl;
			auto monster = monsters.at(i);
			cout<<"名称:"<<monster->getName()<<endl;
			cout<<"描述:"<<monster->getDescription()<<endl;
			cout<<"HP:"<<monster->getCurHP()<<"/"<<monster->getHP()<<endl;
		}
		cout<<"-----------------------------------------------------"<<endl;
		cout<<"主角HP:"<<pPlayer->getCurHP()<<"/"<<pPlayer->getHP()<<endl;
		cout<<"---------------------战斗过程-------------------------"<<endl;
		//为未死亡的怪物排序
		std::vector<Monster*> monsterList;
		for(int i=0;i<monsters.size() && !monsters.at(i)->isDead();i++)
		{
			quit = false;
			monsterList.push_back(monsters.at(i));
		}
		if(quit)
			break;
		std::sort(monsterList.begin(),monsterList.end(),[](Monster*m1,Monster*m2){
			return m1->getAgility() > m2->getAgility();
		});
		//开始攻击判定
		int size = 1 + monsterList.size();
		bool bPlayerAttack = false;
		int j = 0;//将要出手的怪物位置
		for(int i=0;i<size;i++)
		{
			auto monster = j < monsterList.size()?monsterList.at(j):nullptr;
			//主角敏捷高或最后一个出手
			if(!bPlayerAttack &&( !monster || pPlayer->getAgility() > monster->getAgility()))
			{
				//主角攻击
				bPlayerAttack = true;
				do{
					cout<<"-----------------------------------------------------"<<endl;
					cout<<"1.攻击 2.逃跑"<<endl;

					key = GlobalFunctions::getLegalKey();
					if(key == 1)
					{
						if(monsterList.size() == 1)
							pPlayer->attack(monsterList.at(0));
						else
						{
							key = GlobalFunctions::getcha();
							cout<<"攻击第几个"<<endl;
							pPlayer->attack(monsterList.at(key - 1));
						}
						break;
					}
					else if(key == 2)
					{
						break;
					}
					cout<<"输入有误，请重新输入"<<endl;
				}while(true);
				continue;
			}//end 
			monster->attack(pPlayer);
			j++;
		}
		cout<<"按任意键继续"<<endl;
		GlobalFunctions::getcha();
	}
	//战斗结算 获得奖励或者游戏结束
	//获得金钱数
	int gold = 0;
	for(int i=0;i<monsters.size();i++)
		gold += monsters.at(i)->getGold();
	//添加金钱
	DynamicData::getInstance()->alertGold(gold);
	cout<<"战斗胜利，战利品:"<<endl;
	cout<<"金币+"<<gold<<endl;
	GlobalFunctions::getcha();
	system("cls");
}