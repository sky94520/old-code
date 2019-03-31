#ifndef __SDL_TMXTiledMap_H__
#define __SDL_TMXTiledMap_H__
#include<vector>
#include<map>
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
class Tileset;
class TMXObjectGroup;
class TMXTiledMap : public Node
{
private:
	//保存图块集
	std::vector<Tileset*> _tilesets;
	//地图属性集
	std::map<std::string,std::string> _properties;
	//对象集
	std::vector<TMXObjectGroup*> _objectGroup;
	Size _mapSize;
	Size _tileSize;
	int _mapOrientation;//地图方向

public:
	TMXTiledMap();
	~TMXTiledMap();
	static TMXTiledMap*create(const std::string&filename);
	bool init(const std::string&filename);
private:
	bool parse(const std::string&filename);

	void parseTileset(rapidxml::xml_node<>*tileRoot);
	void parseLayer(rapidxml::xml_node<>*layerRoot);
	void parseProperties(rapidxml::xml_node<>*propRoot);
	void parseObjectGroup(rapidxml::xml_node<>*objectLayer);
};
#endif