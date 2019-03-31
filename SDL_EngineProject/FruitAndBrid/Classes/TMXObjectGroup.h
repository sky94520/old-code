#ifndef __SDL_TMXObjectGroup_H__
#define __SDL_TMXObjectGroup_H__
#include<map>
#include<vector>
#include<algorithm>
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
typedef struct TMXObject
{
	std::string id;
	std::string name;
	std::string type;

	float x;
	float y;
	float width;
	float height;

	std::map<std::string,std::string> properties;
public:
	TMXObject()
		:id(""),name(""),type(""),x(0.f),y(0.f),width(0.f),height(0.f)
	{
	}
	TMXObject(rapidxml::xml_node<>*root);
	std::map<std::string,std::string> getProperties()const;
}TMXObject;
class TMXObjectGroup:public Object
{
private:
	std::string _groupName;
	std::vector<TMXObject*> _objects;
public:
	TMXObjectGroup();
	~TMXObjectGroup();
	static TMXObjectGroup*create(rapidxml::xml_node<>*root);
	bool init(rapidxml::xml_node<>*root);

	TMXObject*getObject(const std::string&objectName);
	
	std::string getGroupName()const;
	void setGroupName(const std::string&groupName);
private:
	void parseObject(rapidxml::xml_node<>*root);
};
#endif