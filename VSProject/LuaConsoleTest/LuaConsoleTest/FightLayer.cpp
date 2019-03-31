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
	int time = 1;//��ǰ������
	//��ȡ��Ҫ���ֵĹ���
	//�Լ�����֮�󽫻��õĽ���
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
		cout<<"-----------------------��"<<time++<<"��--------------------"<<endl;
		for(int i=0;i<monsters.size() && !monsters.at(i)->isDead();i++)
		{
			cout<<"����"<<i+1<<endl;
			auto monster = monsters.at(i);
			cout<<"����:"<<monster->getName()<<endl;
			cout<<"����:"<<monster->getDescription()<<endl;
			cout<<"HP:"<<monster->getCurHP()<<"/"<<monster->getHP()<<endl;
		}
		cout<<"-----------------------------------------------------"<<endl;
		cout<<"����HP:"<<pPlayer->getCurHP()<<"/"<<pPlayer->getHP()<<endl;
		cout<<"---------------------ս������-------------------------"<<endl;
		//Ϊδ�����Ĺ�������
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
		//��ʼ�����ж�
		int size = 1 + monsterList.size();
		bool bPlayerAttack = false;
		int j = 0;//��Ҫ���ֵĹ���λ��
		for(int i=0;i<size;i++)
		{
			auto monster = j < monsterList.size()?monsterList.at(j):nullptr;
			//�������ݸ߻����һ������
			if(!bPlayerAttack &&( !monster || pPlayer->getAgility() > monster->getAgility()))
			{
				//���ǹ���
				bPlayerAttack = true;
				do{
					cout<<"-----------------------------------------------------"<<endl;
					cout<<"1.���� 2.����"<<endl;

					key = GlobalFunctions::getLegalKey();
					if(key == 1)
					{
						if(monsterList.size() == 1)
							pPlayer->attack(monsterList.at(0));
						else
						{
							key = GlobalFunctions::getcha();
							cout<<"�����ڼ���"<<endl;
							pPlayer->attack(monsterList.at(key - 1));
						}
						break;
					}
					else if(key == 2)
					{
						break;
					}
					cout<<"������������������"<<endl;
				}while(true);
				continue;
			}//end 
			monster->attack(pPlayer);
			j++;
		}
		cout<<"�����������"<<endl;
		GlobalFunctions::getcha();
	}
	//ս������ ��ý���������Ϸ����
	//��ý�Ǯ��
	int gold = 0;
	for(int i=0;i<monsters.size();i++)
		gold += monsters.at(i)->getGold();
	//��ӽ�Ǯ
	DynamicData::getInstance()->alertGold(gold);
	cout<<"ս��ʤ����ս��Ʒ:"<<endl;
	cout<<"���+"<<gold<<endl;
	GlobalFunctions::getcha();
	system("cls");
}