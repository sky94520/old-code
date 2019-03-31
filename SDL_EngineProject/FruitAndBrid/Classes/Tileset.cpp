#include "Tileset.h"
Tileset::Tileset()
	:firstGrid(0),tileWidth(0),tileHeight(0),
	spacing(0),margin(0),width(0),height(0),
	tileCount(0),name(""),source(""),column(0)
{
}
Tileset::~Tileset()
{
}
Tileset*Tileset::create(rapidxml::xml_node<>*root)
{
	auto tileset = new Tileset();
	if(tileset && tileset->init(root))
		tileset->autoRelease();
	else
		SDL_SAFE_DELETE(tileset);
	return tileset;
}
bool Tileset::init(rapidxml::xml_node<>*root)
{
	//先获取对应的属性
	firstGrid = atoi(root->first_attribute("firstgid")->value());
	name = root->first_attribute("name")->value();
	tileWidth = atoi(root->first_attribute("tilewidth")->value());
	tileHeight = atoi(root->first_attribute("tileheight")->value());

	tileCount = atoi(root->first_attribute("tilecount")->value());
	column = atoi(root->first_attribute("columns")->value());
	if(root->first_attribute("spacing"))
		spacing = atoi(root->first_attribute("spacing")->value());
	if(root->first_attribute("margin"))
		margin = atoi(root->first_attribute("margin")->value());

	for(auto node = root->first_node();node;node = node->next_sibling())
	{
		if(strcmp(node->name(),"image") == 0)
			parseImage(node);
		else if(strcmp(node->name(),"tile") == 0)
			parseTile(node);
	}
	return true;
}
ValueMap Tileset::getPropertiesForGID(int id)
{
	auto iter = _properties.find(id);
	if(iter != _properties.end())
		return iter->second;
	//不存在则返回一个空的valuemap
	return ValueMap();
}
void Tileset::parseImage(rapidxml::xml_node<>*imageRoot)
{
	source = imageRoot->first_attribute("source")->value();
	//TODO
	auto trans = imageRoot->first_attribute("trans")->value();
}
void Tileset::parseTile(rapidxml::xml_node<>*tileRoot)
{
	//解析图块
	std::string idstr = tileRoot->first_attribute("id")->value();
	for(auto node = tileRoot->first_node();node;node = node->next_sibling())
	{
		//animation
		if(strcmp(node->name(),"animation") == 0)
		{
			;
		}
		else if(strcmp(node->name(),"properties") == 0)
		{
			int id = atoi(idstr.c_str());
			parseProperties(id,node);
		}
	}
}
void Tileset::parseProperties(int id,rapidxml::xml_node<>*root)
{
	ValueMap valueMap;
	for(auto node = root->first_node();node;node = node->next_sibling())
	{
		auto key = node->first_attribute("name")->value();
		auto value = node->first_attribute("value")->value();
		valueMap.insert(std::make_pair(key,Value(value)));
	}
	_properties.insert(std::make_pair(id,valueMap));
}