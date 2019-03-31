#ifndef __SDL_TMXTiledMap_H__
#define __SDL_TMXTiledMap_H__
#include<vector>
#include<map>
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
class Tileset;
class TMXLayer;
class TMXObjectGroup;
class TMXTiledMap : public Node
{
private:
	//保存图块集
	std::vector<Tileset*> _tilesets;
	//地图属性集
	ValueMap _properties;
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
	//通过id获取对应的Tileset
	Tileset*getTilesetForGID(int gid)const;
	//获取地图属性
	Value getPropertyForName(const std::string&key)const;
	ValueMap getProperties()const;
	//获得图块属性
	ValueMap getTilePropertiesForGID(int gid)const;
	//通过name获取layer
	TMXLayer*getLayer(const std::string&name);
private:
	bool parse(const std::string&filename);

	void parseTileset(rapidxml::xml_node<>*tileRoot);
	void parseLayer(rapidxml::xml_node<>*layerRoot);
	void parseProperties(rapidxml::xml_node<>*propRoot);
	void parseObjectGroup(rapidxml::xml_node<>*objectLayer);
};
#endif