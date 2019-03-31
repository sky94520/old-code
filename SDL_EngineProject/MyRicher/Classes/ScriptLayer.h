#ifndef __ScriptLayer_H__
#define __ScriptLayer_H__
#include<vector>
#include "SDL_Engine/SDL_Engine.h"

using namespace std;
using namespace SDL;

class ScriptEvent;
class NPC;
enum class TriggerType;

/*�ű��ȴ�����*/
enum class WaitType
{
	None,
	Time,
	Click,
	Button,
};

class ScriptLayer: public Layer
{
	SDL_SYNTHESIZE(WaitType,m_waitType,WaitType);//�ű��ȴ�����
	SDL_SYNTHESIZE(float,m_waitTime,WaitTime);//�ȴ�ʱ��
private:
	vector<NPC*> m_scriptEventList;
	//�����ڽű��н��е�ͼ�л�ʱ��������
	vector<NPC*> m_scriptEventListCopy;
public:
	ScriptLayer();
	~ScriptLayer();
	CREATE_FUNC(ScriptLayer);
	bool init();
	virtual void update(float dt);
	void updateWaitTime(float dt);
	/*�����¼����������Ƿ��ͨ����ǰ�ű��¼�*/
	bool checkAndTriggerScriptEvent(const Rect& boundingBox,int playerID,TriggerType type,int priority);
	//��ȡ�ű��¼�����
	vector<NPC*>& getScriptEventArray();
	vector<NPC*>& getScriptEventArrayCopy();
	//��ӽű��¼�
	void addScriptEvent(NPC*npc);
	//���ȫ���ű��¼�
	void clearScriptEventList();
};
#endif