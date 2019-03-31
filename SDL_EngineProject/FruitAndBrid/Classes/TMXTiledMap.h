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
	//����ͼ�鼯
	std::vector<Tileset*> _tilesets;
	//��ͼ���Լ�
	ValueMap _properties;
	//����
	std::vector<TMXObjectGroup*> _objectGroup;
	Size _mapSize;
	Size _tileSize;
	int _mapOrientation;//��ͼ����

public:
	TMXTiledMap();
	~TMXTiledMap();
	static TMXTiledMap*create(const std::string&filename);
	bool init(const std::string&filename);
	//ͨ��id��ȡ��Ӧ��Tileset
	Tileset*getTilesetForGID(int gid)const;
	//��ȡ��ͼ����
	Value getPropertyForName(const std::string&key)const;
	ValueMap getProperties()const;
	//���ͼ������
	ValueMap getTilePropertiesForGID(int gid)const;
	//ͨ��name��ȡlayer
	TMXLayer*getLayer(const std::string&name);
private:
	bool parse(const std::string&filename);

	void parseTileset(rapidxml::xml_node<>*tileRoot);
	void parseLayer(rapidxml::xml_node<>*layerRoot);
	void parseProperties(rapidxml::xml_node<>*propRoot);
	void parseObjectGroup(rapidxml::xml_node<>*objectLayer);
};
#endif