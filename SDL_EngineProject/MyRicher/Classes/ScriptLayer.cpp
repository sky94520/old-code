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
			//ֻ����Ӧ�ø��µ�ʱ��Ż����update����
			if (script->isShouldUpdate())
				script->updateScript(dt);
			it++;
		}
		else//ɾ��
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
		//�ص�����
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
	//�Ƿ��̲��¼�
	bool bSwallowed = false;

	for (auto it = m_scriptEventList.begin();it != m_scriptEventList.end();it++)
	{
		auto script = *it;

		//������ײ �ű���ͬ
		if (!script->isDirty() && script->getUniqueID() != playerID 
			&& script->intersectRect(boundingBox))
		{
			//����������ͬ ���ȼ���ͬ ����û���̲��¼� ���ö�Ӧ�Ľű�
			if (script->isCanTrigger(type) && (script->getPriority() & priority)
				&& !bSwallowed)
			{
				bSwallowed = script->executeScript(playerID);
			}
			//ֻ���ڴ�������������ͬ��ʱ�Ż��ж��Ƿ����ײ
			if (script->getPriority() == PRIORITY_SAME)
			{
				bPassing &= script->isPassing();
			}
		}
	}
	//���luaջ
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
