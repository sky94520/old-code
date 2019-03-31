#include "TMXTiledMap.h"
#include "Tileset.h"
#include "TMXObjectGroup.h"
TMXTiledMap::TMXTiledMap()
	:_mapSize(Size::ZERO)
	,_tileSize(Size::ZERO)
	,_mapOrientation(90)//默认为90度
{
}
TMXTiledMap::~TMXTiledMap()
{
	_properties.clear();

	for(auto iter = _tilesets.begin();iter != _tilesets.end();)
	{
		auto tileset = *iter;
		iter = _tilesets.erase(iter);
		tileset->release();
	}
	for(auto iter = _objectGroup.begin();iter != _objectGroup.end();)
	{
		auto objectGroup = *iter;
		iter = _objectGroup.erase(iter);
		objectGroup->release();
	}
}
TMXTiledMap*TMXTiledMap::create(const std::string&filename)
{
	auto tiledMap = new TMXTiledMap();
	if(tiledMap && tiledMap->init(filename))
		tiledMap->autoRelease();
	else
		SDL_SAFE_DELETE(tiledMap);
	return tiledMap;
}
bool TMXTiledMap::init(const std::string&filename)
{
	return parse(filename);
}
bool TMXTiledMap::parse(const std::string&filename)
{
	rapidxml::xml_document<> doc;
	rapidxml::file<> file(filename.c_str());
	doc.parse<0>(file.data());
	//root 结点 map
	rapidxml::xml_node<>*root = doc.first_node();
	std::string orientation = root->first_attribute("orientation")->value();
	std::string renderorder = root->first_attribute("renderorder")->value();
	auto width = atoi(root->first_attribute("width")->value());
	auto height = atoi(root->first_attribute("height")->value());
	auto tileWidth = atoi(root->first_attribute("tilewidth")->value());
	auto tileHeight = atoi(root->first_attribute("tileheight")->value());
	auto nextobjectid = root->first_attribute("nextobjectid")->value();
	//仅支持right down朝向
	if(renderorder != "right-down")
		return false;
	//赋值
	_mapSize = Size(width,height);
	_tileSize = Size(tileWidth,tileHeight);
	//todo
	if(orientation == "orthogonal")
		_mapOrientation = 90;
	for(auto node = root->first_node();node;node = node->next_sibling())
	{
		std::string name = node->name();
		if(name == "tileset")//解析图块
			parseTileset(node);
		else if(name == "layer")
			parseLayer(node);
		else if(name == "properties")
			parseProperties(node);
		else if(name == "objectgroup")
			parseObjectGroup(node);
	}
	return true;
}
void TMXTiledMap::parseTileset(rapidxml::xml_node<>*tileRoot)
{
	auto tileset = Tileset::create(tileRoot);
	if(tileset)
	{
		tileset->retain();
		_tilesets.push_back(tileset);
		//可以在这加载图片
	}
}
void TMXTiledMap::parseLayer(rapidxml::xml_node<>*layerRoot)
{
	printf("layer");
}
void TMXTiledMap::parseProperties(rapidxml::xml_node<>*propRoot)
{
	for(auto node = propRoot->first_node();node;node = node->next_sibling())
	{
		auto key = node->first_attribute("name")->value();
		auto value = node->first_attribute("value")->value();

		_properties.insert(std::make_pair(key,value));
	}
}
void TMXTiledMap::parseObjectGroup(rapidxml::xml_node<>*objectRoot)
{
	auto objectGroup = TMXObjectGroup::create(objectRoot);
	objectGroup->retain();
	_objectGroup.push_back(objectGroup);
}