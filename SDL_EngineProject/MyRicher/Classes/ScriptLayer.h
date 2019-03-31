#ifndef __ScriptLayer_H__
#define __ScriptLayer_H__
#include<vector>
#include "SDL_Engine/SDL_Engine.h"

using namespace std;
using namespace SDL;

class ScriptEvent;
class NPC;
enum class TriggerType;

/*脚本等待类型*/
enum class WaitType
{
	None,
	Time,
	Click,
	Button,
};

class ScriptLayer: public Layer
{
	SDL_SYNTHESIZE(WaitType,m_waitType,WaitType);//脚本等待类型
	SDL_SYNTHESIZE(float,m_waitTime,WaitTime);//等待时间
private:
	vector<NPC*> m_scriptEventList;
	//避免在脚本中进行地图切换时发生错误
	vector<NPC*> m_scriptEventListCopy;
public:
	ScriptLayer();
	~ScriptLayer();
	CREATE_FUNC(ScriptLayer);
	bool init();
	virtual void update(float dt);
	void updateWaitTime(float dt);
	/*触发事件，并返回是否可通过当前脚本事件*/
	bool checkAndTriggerScriptEvent(const Rect& boundingBox,int playerID,TriggerType type,int priority);
	//获取脚本事件数组
	vector<NPC*>& getScriptEventArray();
	vector<NPC*>& getScriptEventArrayCopy();
	//添加脚本事件
	void addScriptEvent(NPC*npc);
	//清除全部脚本事件
	void clearScriptEventList();
};
#endif