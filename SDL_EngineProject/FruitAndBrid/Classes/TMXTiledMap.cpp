#include "TMXTiledMap.h"
#include "Tileset.h"
#include "TMXObjectGroup.h"
#include "TMXLayer.h"
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
	auto file = FileUtils::getInstance()->fullPathForFilename(filename);
	if(file.empty())
		return false;
	return parse(file);
}
Tileset*TMXTiledMap::getTilesetForGID(int gid)const
{
	if(gid == 0)
		return nullptr;
	for(auto i = 0;i < _tilesets.size();i++)
	{
		auto firstGrid = _tilesets.at(i)->firstGrid;
		auto tileCount = _tilesets.at(i)->tileCount;
		if(gid >= firstGrid && gid < firstGrid + tileCount)
			return _tilesets.at(i);
	}
	return nullptr;
}
Value TMXTiledMap::getPropertyForName(const std::string&key)const
{
	if(_properties.find(key) != _properties.end())
		return _properties.at(key);
	return Value();
}
ValueMap TMXTiledMap::getProperties()const
{
	return _properties;
}
ValueMap TMXTiledMap::getTilePropertiesForGID(int gid)const
{
	auto tileset = this->getTilesetForGID(gid);
	if(tileset)
	{
		return tileset->getPropertiesForGID(gid - tileset->firstGrid + 1);
	}
	return ValueMap();
}
TMXLayer*TMXTiledMap::getLayer(const std::string&name)
{
	if(name.empty())
		return nullptr;
	for(auto child:_children)
	{
		TMXLayer*layer = dynamic_cast<TMXLayer*>(child);
		if(layer && name.compare(layer->getName()) == 0)
		{
			return layer;
		}
	}
	return nullptr;
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
	else if(orientation == "isometric")
		_mapOrientation = 45;
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
		//加载图片
		Director::getInstance()->getTextureCache()->addImage(tileset->source);
	}
}
void TMXTiledMap::parseLayer(rapidxml::xml_node<>*layerRoot)
{
	TMXLayer*layer = TMXLayer::create(layerRoot);
	this->addChild(layer);
	//生成Sprite
	auto datas = layer->_data;
	auto width = layer->_width;
	auto height = layer->_height;
	int id = -1;
	for(int rows = 0;rows < height;rows++)
	{
		for(int cols = 0;cols < width;cols++)
		{
			id = datas[rows][cols];
			Tileset*tileset = this->getTilesetForGID(id);
			if(tileset == nullptr)
				continue;
			auto image = tileset->source;
			auto margin = tileset->margin;
			auto spacing = tileset->spacing;
			auto tileWidth = tileset->tileWidth;
			auto tileHeight = tileset->tileHeight;

			Texture*texture = Director::getInstance()->getTextureCache()->getTextureForKey(image);
			auto currentRow = (id - tileset->firstGrid)/tileset->column;
			auto currentFrame = (id - tileset->firstGrid)%tileset->column;
			Rect rect = Rect(margin + (spacing + tileWidth)*currentFrame,
				margin + (spacing + tileHeight)*currentRow,tileWidth,tileHeight);

			Sprite*sprite = Sprite::createWithTexture(texture,rect,false,Point(0,0),Size(tileHeight,tileWidth));
			sprite->setPosition(cols * _tileSize.width,rows * _tileSize.height);
			sprite->setTag(id);

			layer->addChild(sprite);
		}
	}
}
void TMXTiledMap::parseProperties(rapidxml::xml_node<>*propRoot)
{
	for(auto node = propRoot->first_node();node;node = node->next_sibling())
	{
		auto key = node->first_attribute("name")->value();
		auto value = node->first_attribute("value")->value();

		_properties.insert(std::make_pair(key,Value(value)));
	}
}
void TMXTiledMap::parseObjectGroup(rapidxml::xml_node<>*objectRoot)
{
	auto objectGroup = TMXObjectGroup::create(objectRoot);
	objectGroup->retain();
	_objectGroup.push_back(objectGroup);
}