#include "ScriptLayer.h"
#include "ScriptEvent.h"
#include "NPC.h"
#include "GameScene.h"

ScriptLayer::ScriptLayer()
	:m_waitType(WaitType::None)
	,m_waitTime(0.f)
{
}

ScriptLayer::~ScriptLayer()
{
	for (auto it = m_scriptEventList.begin();it != m_scriptEventList.end();)
	{
		auto script = *it;

		script->clearScript();
		SDL_SAFE_RELEASE(script);

		it = m_scriptEventList.erase(it);
	}
}

bool ScriptLayer::init()
{
	return true;
}

void ScriptLayer::update(float dt)
{
	for (auto it = m_scriptEventListCopy.begin();it != m_scriptEventListCopy.end();)
	{
		auto npc = *it;
		
		m_scriptEventList.push_back(npc);

		it = m_scriptEventListCopy.erase(it);
	}
	for (auto it = m_scriptEventList.begin();it != m_scriptEventList.end();)
	{
		auto script = *it;

		if (!script->isDirty())
		{
			//只有在应该更新的时候才会调用update函数
			if (script->isShouldUpdate())
				script->updateScript(dt);
			it++;
		}
		else//删除
		{
			script->clearScript();
			script->removeFromParent();

			SDL_SAFE_RELEASE_NULL(script);

			it = m_scriptEventList.erase(it);
		}
	}
}

void ScriptLayer::updateWaitTime(float dt)
{
	if (m_waitType == WaitType::Time)
	{
		m_waitTime -= dt;
		//回调函数
		if (m_waitTime <= 0.f)
		{
			m_waitTime = 0.f;
			GameScene::getInstance()->scriptWaitEnd();
		}
	}
}

bool ScriptLayer::checkAndTriggerScriptEvent(const Rect& boundingBox,int playerID,TriggerType type,int priority)
{
	bool bPassing = true;
	//是否吞并事件
	bool bSwallowed = false;

	for (auto it = m_scriptEventList.begin();it != m_scriptEventList.end();it++)
	{
		auto script = *it;

		//发生碰撞 脚本不同
		if (!script->isDirty() && script->getUniqueID() != playerID 
			&& script->intersectRect(boundingBox))
		{
			//触发条件相同 优先级相同 并且没有吞并事件 调用对应的脚本
			if (script->isCanTrigger(type) && (script->getPriority() & priority)
				&& !bSwallowed)
			{
				bSwallowed = script->executeScript(playerID);
			}
			//只有在触发条件和主角同级时才会判断是否会碰撞
			if (script->getPriority() == PRIORITY_SAME)
			{
				bPassing &= script->isPassing();
			}
		}
	}
	//清除lua栈
	GameScene::getInstance()->luaSetTop(0);

	return bPassing;
}

vector<NPC*>& ScriptLayer::getScriptEventArray()
{
	return m_scriptEventList;
}

vector<NPC*>& ScriptLayer::getScriptEventArrayCopy()
{
	return m_scriptEventListCopy;
}

void ScriptLayer::addScriptEvent(NPC*npc)
{
	SDL_SAFE_RETAIN(npc);
	m_scriptEventListCopy.push_back(npc);
}

void ScriptLayer::clearScriptEventList()
{
	for (auto it = m_scriptEventList.begin();it != m_scriptEventList.end();it++)
	{
		auto script = *it;

		script->setDirty(true);
	}
}
