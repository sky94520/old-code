#ifndef __StateParser_H__
#define __StateParser_H__

#include<iostream>
#include<vector>
#include<memory>

#include "tinyxml.h"

class GameObject;

class StateParser
{
    private:
    void parseObjects(TiXmlElement*pStateRoot,std::vector<GameObject*> *pObjects);
    void parseTextures(TiXmlElement*pStateRoot,std::vector<std::string> *pTextureIDs);
  public:
    bool parseState(const char*stateFile,std::string stateID,std::vector<GameObject*>*pObjects,std::vector<std::string>*pTextureIDs);
};
#endif
