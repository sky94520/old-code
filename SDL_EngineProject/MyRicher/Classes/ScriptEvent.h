#ifndef __ScriptEvent_H__
#define __ScriptEvent_H__

#include<string>
#include "Entity.h"
#include "lua/lua.h"

#define PRIORITY_LOW  1
#define PRIORITY_SAME 2
#define PRIORITY_HIGH 4
using namespace std;
/*触发方式*/
enum class TriggerType
{
	None,
	OKButton,/*确定键*/
	TouchWithPlayer,/*和玩家接触*/
	All,/*包含上面两个*/
};

class ScriptEvent
{
	SDL_SYNTHESIZE(TriggerType,m_triggerType,TriggerType);
	SDL_BOOL_SYNTHESIZE(m_bDirty,Dirty);//是否是脏的
	SDL_BOOL_SYNTHESIZE(m_bShouldUpdate,ShouldUpdate);//是否应该调用update函数
	SDL_SYNTHESIZE_READONLY(int,m_nPriority,Priority);//优先级
protected:
	string m_scriptName;//脚本名称
	string m_scriptFilename;//脚本文件名
	Rect m_boundingBox;
	string _chartletName;
public:
	ScriptEvent();
	~ScriptEvent();
	bool initlize(const ValueMap& object,int id);
	//执行对应的脚本 返回值 为true是否吞并事件
	bool executeScript(int playerID);
	void updateScript(float dt);
	void clearScript();
	//是否能触发
	bool isCanTrigger(TriggerType triggerType);
	bool isPassing()const;
public:
	static TriggerType getTriggerTypeByString(const string& str);
private:
	void scheduleOnce(const ccScheduleCallback& callback,const std::string&key,float delay=0.f);
};
#endif