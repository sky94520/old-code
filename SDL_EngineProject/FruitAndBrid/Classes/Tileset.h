#ifndef __SDL_Tileset_H__
#define __SDL_Tileset_H__
#include<string>
#include<unordered_map>
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
class Tileset:public Object
{
public:
	int firstGrid;
	int tileWidth;
	int tileHeight;

	int spacing;
	int margin;

	int width;
	int height;

	int tileCount;
	int column;

	std::string name;
	std::string source;
private:
	std::unordered_map<int,ValueMap> _properties;
public:
	Tileset();
	~Tileset();
	static Tileset*create(rapidxml::xml_node<>*root);
	bool init(rapidxml::xml_node<>*root);
	//获取对应id图块的属性
	//id 以0开始
	ValueMap getPropertiesForGID(int id);
private:
	void parseImage(rapidxml::xml_node<>*imageRoot);
	void parseTile(rapidxml::xml_node<>*tileRoot);
	void parseProperties(int id,rapidxml::xml_node<>*root);
};
#endif