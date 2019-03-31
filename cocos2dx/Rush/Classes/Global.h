#ifndef __Global_H__
#define __Global_H__
class MonsterManager;
class Global
{
public:
	MonsterManager*_monsterManager;
private:
	static Global*g_pInstance;
	Global();
	~Global();
public:
	static Global* getInstance();
};
#endif