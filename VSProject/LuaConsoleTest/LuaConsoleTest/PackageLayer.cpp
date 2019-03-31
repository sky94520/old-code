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
	//��ȡ����
	int key = 0;
	//�Ƿ��˳�ѭ��
	bool quit = false;
	//��������
	auto pItems = DynamicData::getInstance()->getPackages();
	auto gold =0;
	//�����һ֡
	system("cls");
	//ѭ��
	while(quit == false)
	{
		//��Ϊ���ʱ���ڱ仯�����Ե�ÿ��ѭ�������»�ȡ
		gold = DynamicData::getInstance()->getGold();
		std::cout<<"-------------------------����-------------------------"<<std::endl;
		cout<<"���:"<<gold<<endl;
		std::cout<<"------------------------------------------------------"<<std::endl;
		for(int i=0;i < pItems->size();++i)
		{
			//ǿ������ת��
			auto item = pItems->at(i);
			std::cout<<i+1<<".";
			if(item->getItemType() == ItemType::kItemType_Weapon)
			{
				std::string equipped = dynamic_cast<Weapon*>(item)->isEquipped()?"[��װ��]":"";
				std::cout<<equipped;
			}
			auto name = item->getName();
			auto des = item->getDescription();
			std::cout<<name<<std::endl;
		}
		std::cout<<"------------------------------------------------------"<<std::endl;
		std::cout<<"0.���ص���һ����"<<endl;
		cout<<"���ĳһװ������ȡ��ϸ��Ϣ"<<endl;
		std::cout<<"------------------------------------------------------"<<std::endl;
		//��ȡ����
		key = GlobalFunctions::getLegalKey();
		//������һ����
		if(key == 0)
		{
			quit = true;
			return ;
		}
		//��ȡ���ߵľ�������
		auto item = pItems->at(key-1);
		std::cout<<item->toString()<<std::endl;
		std::cout<<"------------------------------------------------------"<<std::endl;
		cout<<"1.װ��/ʹ��   2.����    0.������һ����"<<endl;
		std::cout<<"------------------------------------------------------"<<std::endl;
		key = GlobalFunctions::getLegalKey();
		switch(key)
		{
		case 1:
			{
				bool bRet = m_pDelegate->use(item);
				if(bRet)
					cout<<"ʹ�óɹ�"<<endl;
				else
					cout<<"ʹ��ʧ��!"<<endl;
				cout<<"�����������"<<endl;
				GlobalFunctions::getcha();
			}
			break;
		case 2:
			{
				int price = m_pDelegate->sell(item);
				if(price < 0)
					cout<<"ʹ��ʧ��"<<endl;
				else
					cout<<"���۳ɹ���������"<<price<<"���"<<endl;
				cout<<"�����������"<<endl;
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