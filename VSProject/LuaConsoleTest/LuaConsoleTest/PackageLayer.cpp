#include "PackageLayer.h"
#include "Weapon.h"
#include "GlobalFunctions.h"
#include "DynamicData.h"
PackageLayer::PackageLayer()
	:m_pDelegate(nullptr)
{
}
PackageLayer::~PackageLayer()
{
}
bool PackageLayer::init()
{
	return true;
}
void PackageLayer::show()
{
	//获取按键
	int key = 0;
	//是否退出循环
	bool quit = false;
	//背包内容
	auto pItems = DynamicData::getInstance()->getPackages();
	auto gold =0;
	//清除上一帧
	system("cls");
	//循环
	while(quit == false)
	{
		//因为金币时刻在变化，所以得每次循环都重新获取
		gold = DynamicData::getInstance()->getGold();
		std::cout<<"-------------------------背包-------------------------"<<std::endl;
		cout<<"金币:"<<gold<<endl;
		std::cout<<"------------------------------------------------------"<<std::endl;
		for(int i=0;i < pItems->size();++i)
		{
			//强制类型转换
			auto item = pItems->at(i);
			std::cout<<i+1<<".";
			if(item->getItemType() == ItemType::kItemType_Weapon)
			{
				std::string equipped = dynamic_cast<Weapon*>(item)->isEquipped()?"[已装备]":"";
				std::cout<<equipped;
			}
			auto name = item->getName();
			auto des = item->getDescription();
			std::cout<<name<<std::endl;
		}
		std::cout<<"------------------------------------------------------"<<std::endl;
		std::cout<<"0.返回到上一界面"<<endl;
		cout<<"点击某一装备来获取详细信息"<<endl;
		std::cout<<"------------------------------------------------------"<<std::endl;
		//获取按键
		key = GlobalFunctions::getLegalKey();
		//返回上一界面
		if(key == 0)
		{
			quit = true;
			return ;
		}
		//获取道具的具体描述
		auto item = pItems->at(key-1);
		std::cout<<item->toString()<<std::endl;
		std::cout<<"------------------------------------------------------"<<std::endl;
		cout<<"1.装备/使用   2.出售    0.返回上一界面"<<endl;
		std::cout<<"------------------------------------------------------"<<std::endl;
		key = GlobalFunctions::getLegalKey();
		switch(key)
		{
		case 1:
			{
				bool bRet = m_pDelegate->use(item);
				if(bRet)
					cout<<"使用成功"<<endl;
				else
					cout<<"使用失败!"<<endl;
				cout<<"按任意键继续"<<endl;
				GlobalFunctions::getcha();
			}
			break;
		case 2:
			{
				int price = m_pDelegate->sell(item);
				if(price < 0)
					cout<<"使用失败"<<endl;
				else
					cout<<"出售成功，你获得了"<<price<<"金币"<<endl;
				cout<<"按任意键继续"<<endl;
				GlobalFunctions::getcha();
			}
			break;
		}
		system("cls");
	}//end while(quit == false)
}
void PackageLayer::setDelegate(PackageLayerDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}