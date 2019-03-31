#pragma once

#include<iostream>
#include<vector>

#include "tinyxml.h"
#include "LoaderParams.h"
#include "GameObjectFactory.h"
#include "TextureManager.h"
#include "GameObject.h"
//class GameObject;

class StateParser
{
    private:
    void parseObjects(TiXmlElement*pStateRoot,std::vector<GameObject*> *pObjects);
    void parseTextures(TiXmlElement*pStateRoot,std::vector<std::string> *pTextureIDs);
  public:
    bool parseState(const char*stateFile,std::string stateID,std::vector<GameObject*>*pObjects,std::vector<std::string>*pTextureIDs);
};
