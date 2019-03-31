#ifndef __ScriptEvent_H__
#define __ScriptEvent_H__

#include<string>
#include "Entity.h"
#include "lua/lua.h"

#define PRIORITY_LOW  1
#define PRIORITY_SAME 2
#define PRIORITY_HIGH 4
using namespace std;
/*������ʽ*/
enum class TriggerType
{
	None,
	OKButton,/*ȷ����*/
	TouchWithPlayer,/*����ҽӴ�*/
	All,/*������������*/
};

class ScriptEvent
{
	SDL_SYNTHESIZE(TriggerType,m_triggerType,TriggerType);
	SDL_BOOL_SYNTHESIZE(m_bDirty,Dirty);//�Ƿ������
	SDL_BOOL_SYNTHESIZE(m_bShouldUpdate,ShouldUpdate);//�Ƿ�Ӧ�õ���update����
	SDL_SYNTHESIZE_READONLY(int,m_nPriority,Priority);//���ȼ�
protected:
	string m_scriptName;//�ű�����
	string m_scriptFilename;//�ű��ļ���
	Rect m_boundingBox;
	string _chartletName;
public:
	ScriptEvent();
	~ScriptEvent();
	bool initlize(const ValueMap& object,int id);
	//ִ�ж�Ӧ�Ľű� ����ֵ Ϊtrue�Ƿ��̲��¼�
	bool executeScript(int playerID);
	void updateScript(float dt);
	void clearScript();
	//�Ƿ��ܴ���
	bool isCanTrigger(TriggerType triggerType);
	bool isPassing()const;
public:
	static TriggerType getTriggerTypeByString(const string& str);
private:
	void scheduleOnce(const ccScheduleCallback& callback,const std::string&key,float delay=0.f);
};
#endif