#include "NPC.h"
#include "GameScene.h"

NPC::NPC()
{
}

NPC::~NPC()
{
}

NPC* NPC::create(const ValueMap& object)
{
	auto npc = new NPC();

	if (npc && npc->init(object))
		npc->autoRelease();
	else
		SDL_SAFE_DELETE(npc);

	return npc;
}

bool NPC::init()
{
	return true;
}

bool NPC::init(const ValueMap& object)
{
	bool bRet = false;
	
	int width = object.at("width").asInt();
	int height = object.at("height").asInt();

	int uniqueID = this->getUniqueID();
	//���нű��ĳ�ʼ��
	bRet |= ScriptEvent::initlize(object,uniqueID);
	//��ȡ��ͼ
	auto chartletName = this->_chartletName;
	auto size = m_boundingBox.size;
	auto origin = m_boundingBox.origin;
	//TODO
	if (!chartletName.empty())
	{
		Entity::bindSpriteWithSpriteFrameName(chartletName);
	}
	else if (this->getSprite() == nullptr)
	{
		this->setContentSize(size);
	}
	this->setPosition(Point(origin.x + size.width/2,origin.y + size.height/2));

	return bRet;
}

bool NPC::intersectRect(const Rect& rect)
{
	//�鿴��Ӧtable���Ƿ�����ֶ�range
	auto gameScene = GameScene::getInstance();

	Value value = gameScene->getValueOfTable(m_scriptName,"range");
	//��������ڣ��鿴�����Ƿ���ײ
	if (value.getType() == Value::Type::NONE)
	{
		auto r = this->getBoundingBox();
		return r.intersectRect(rect);
	}
	
	auto range = value.asString();

	if (range == "all")
		return true;
	//TODO
	return m_boundingBox.intersectRect(rect);
}