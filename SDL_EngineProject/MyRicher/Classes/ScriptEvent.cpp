#include "ScriptEvent.h"
#include "GameScene.h"

ScriptEvent::ScriptEvent()
	:m_triggerType(TriggerType::None)
	,m_bDirty(false)
	,m_bShouldUpdate(false)
	,m_nPriority(0)
{
}

ScriptEvent::~ScriptEvent()
{
}

bool ScriptEvent::initlize(const ValueMap& object,int id)
{
	int x = object.at("x").asInt();
	int y = object.at("y").asInt();
	int width = object.at("width").asInt();
	int height = object.at("height").asInt();
	//获取脚本名
	m_scriptName = object.at("name").asString();
	//获取对应属性
	const auto& properties = object.at("properties").asValueMap();

	m_scriptFilename = properties.at("script").asString();
	m_nPriority = properties.at("priority").asInt();
	//动画名可能不存在
	if (properties.find("chartlet") != properties.end())
	{
		_chartletName = properties.at("chartlet").asString();
	}
	if (properties.find("update") != properties.end())
	{
		m_bShouldUpdate = properties.at("update").asBool();
	}
	auto triggerStr = properties.at("trigger").asString();
	m_triggerType = this->getTriggerTypeByString(triggerStr);
	//设置碰撞面积
	m_boundingBox.origin = Point(x,y);
	m_boundingBox.size = Size(width,height);
	
	auto gameScene = GameScene::getInstance();
	//执行脚本
	int ret = LUA_OK; 
	if (!m_scriptFilename.empty())
	{
		gameScene->luaDoFile(m_scriptFilename);
	}
	//脚本加载成功，调用对应的初始化函数
	if (ret == LUA_OK)
	{
		Value value(id);
		gameScene->luaPcall(m_scriptName,"initlize",0,&value,NULL);

		return true;
	}
	else
	{
		printf("ScriptEvent::init error:%s\n",gameScene->luaLCheckString(-1));
	}

	return false;
}

bool ScriptEvent::executeScript(int playerID)
{
	auto gameScene = GameScene::getInstance();
	bool ret = false;

	Value value(playerID);
	auto results = gameScene->luaPcall(m_scriptName,"execute",1,&value,NULL);
	//存在返回值
	if (!results.empty())
	{
		ret = results.front().asBool();
	}

	return ret;
}

void ScriptEvent::updateScript(float dt)
{
	auto gameScene = GameScene::getInstance();

	Value value(dt);
	gameScene->luaPcall(m_scriptName,"update",0,&value,NULL);
}

void ScriptEvent::clearScript()
{
	auto gameScene = GameScene::getInstance();

	if(gameScene != nullptr)
		gameScene->luaPcall(m_scriptName,"clean",0,NULL);
}

bool ScriptEvent::isCanTrigger(TriggerType triggerType)
{
	if (triggerType == TriggerType::All)
		return true;
	
	return this->m_triggerType == triggerType;
}

bool ScriptEvent::isPassing()const
{
	return m_nPriority != PRIORITY_SAME;
}

TriggerType ScriptEvent::getTriggerTypeByString(const string& str)
{
	TriggerType type = TriggerType::None;

	if (str == "TouchWithPlayer")
		type = TriggerType::TouchWithPlayer;
	else if (str == "OKButton")
		type = TriggerType::OKButton;

	return type;
}

void ScriptEvent::scheduleOnce(const ccScheduleCallback&callback,const std::string&key,float delay)
{
	auto scheduler = Director::getInstance()->getScheduler();
	auto gameScene = GameScene::getInstance();

	scheduler->schedule(callback,gameScene,key,0,1,delay,!gameScene->isRunning());
}
