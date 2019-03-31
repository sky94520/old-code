#pragma once
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
};
typedef GameObjectFactory TheGameObjectFactory;
