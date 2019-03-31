#ifndef __GameObjectFactory_H__
#define __GameObjectFactory_H__

#include<string>
#include<map>
#include<iostream>

#include "GameObject.h"

class BaseCreator
{
public:
    virtual GameObject*createGameObject() const = 0;
    //virtual ~BaseCreator();
};
class GameObjectFactory
{
private:
    std::map<std::string,BaseCreator*> m_creators;
    static GameObjectFactory*s_pInstance;
private:
    GameObjectFactory();
public:
    bool registerType(std::string typeID,BaseCreator*pCreator);
    GameObject*create(std::string typeID);

    static GameObjectFactory*Instance();
    //从map中清除id的Object Factory
    void clearFromObjectFactoryMap(std::string id);
};
typedef GameObjectFactory TheGameObjectFactory;
#endif
