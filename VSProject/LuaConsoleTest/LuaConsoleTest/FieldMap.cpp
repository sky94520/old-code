#include "FieldMap.h"
#include "MainLua.h"
#include "StringUtils.h"
#include "Monster.h"
#include "Player.h"
#include "SEMath.h"
#include "TextureManager.h"
void TransferMatrix::collided()
{
	m_pOwner->getDelegate()->toggleLayer(this->mapFile,Point(x,y));
}
FieldMap::FieldMap()
	:m_nCurStep(0),m_pDelegate(nullptr)
{
	//����2��monster
	for(int i=0;i<2;i++)
		m_monsterList.push_back(new Monster());
	//����4��������
	for(int i=0;i<4;i++)
	{
		auto matrix = new TransferMatrix();
		matrix->m_pOwner = this;
		m_transferMatrixs.push_back(matrix);
	}
}
FieldMap::~FieldMap()
{
	for(int i=0;i<m_transferMatrixs.size();i++)
	{
		delete m_transferMatrixs.at(i);
	}
	m_transferMatrixs.clear();
	for(int i=0;i<m_monsterList.size();i++)
		delete m_monsterList.at(i);
	m_monsterList.clear();
	m_monsterStrs.clear();
}
bool FieldMap::init(const std::string&filename)
{
	//���ض�Ӧ��lua����Ϊmap��һ�������Բ������Ӷ�Ӧ�Ŀռ�
	auto pL = MainLua::getInstance();
	luaL_dofile(pL->getLuaState(),filename.c_str());
	//��ȡ��������
	m_name = MainLua::getInstance()->getStringFromTable("map","name");
	m_descrption = MainLua::getInstance()->getStringFromTable("map","description");

	m_nStep = MainLua::getInstance()->getIntegerFromTable("map","step");
	m_nLevel = MainLua::getInstance()->getIntegerFromTable("map","level");
	auto strs = MainLua::getInstance()->getStringFromTable("map","monsters");
	m_monsterStrs = StringUtils::split(strs,",");
	//���ò���
	m_nCurStep = 0;
	//���ô�����
	for(int i=0;i<m_transferMatrixs.size();i++)
		m_transferMatrixs.at(i)->bAlived = false;
	initTransferMatrix();
	return true;
}
void FieldMap::createMonsters()
{
	//�����ʼ��һ������
	//todo
	auto location = RANDOM(0,m_monsterStrs.size());
	auto id = m_monsterStrs.at(location);
	//��ʼ��
	Monster*monster = nullptr;
	for(int i=0;i<m_monsterList.size();i++)
		if(m_monsterList.at(i)->isDead())
		{
			monster = m_monsterList.at(i);
			break;
		}
	monster->init(id.asString());
}
void FieldMap::render()
{
	cout<<"��ͼ����:"<<m_name<<endl;
	cout<<"��ͼ����:"<<m_descrption<<endl;
	cout<<"��ͼ�ȼ�:"<<m_nLevel<<endl;
	m_nCurStep++;
	if(m_nCurStep > m_nStep)
	{
		printf("����ս������");
		//���ɵ���
		createMonsters();
		m_pDelegate->fight();
		m_nCurStep = 0;
	}
	auto player = m_pDelegate->getPlayer();
	//�ж��Ƿ񵽴ﴫ���󣬵������ת
	for(int i=0;i<m_transferMatrixs.size();i++)
	{
		auto m = m_transferMatrixs.at(i);
		if(m->bAlived)
		{
			TextureManager::getInstance()->draw(m->x,m->y,'O');
			if(m->x == player->getPosition().x && m->y == player->getPosition().y)
				m_pDelegate->setColliabledEntity(m);
		}
	}
}
std::vector<Monster*>* FieldMap::getMonsters()
{
	return &m_monsterList;
}
void FieldMap::setDelegate(FieldMapDelegate*pDelegate)
{
	m_pDelegate = pDelegate;
}
FieldMapDelegate* FieldMap::getDelegate()const
{
	return m_pDelegate;
}
void FieldMap::initTransferMatrix()
{
	//��ȡ���������
	auto size = MainLua::getInstance()->getIntegerFromTable("TransferMatrix","size");
	for(int i=0;i<size;i++)
	{
		auto transferMatrix = m_transferMatrixs.at(i);
		//��ȡ����ֵ
		std::string key = StringUtils::format("TransferMatrix%d",i+1);
		transferMatrix->x = MainLua::getInstance()->getIntegerFromTable(key.c_str(),"x");
		transferMatrix->y = MainLua::getInstance()->getIntegerFromTable(key.c_str(),"y");
		transferMatrix->mapFile = MainLua::getInstance()->getStringFromTable(key.c_str(),"mapFile");
		transferMatrix->bAlived = true;
	}
}