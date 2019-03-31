#ifndef __SDL_TMXLayer_H__
#define __SDL_TMXLayer_H__
#include<vector>
#include<string>
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
class TMXTiledMap;
class TMXLayer : public Layer
{
private:
	friend class TMXTiledMap;
private:
	std::string _layerName;
	//保存着该layer解压缩后的数据
	std::vector<std::vector<int> > _data;
	int _width;
	int _height;
public:
	TMXLayer();
	~TMXLayer();
	static TMXLayer*create(rapidxml::xml_node<>*root);
	bool init(rapidxml::xml_node<>*root);
	//根据坐标获取对应gid
	//pos param 为地图相应坐标
	int getTileGIDAt(const Point&tileCoordinate)const;

	std::string getLayerName()const;
private:
	bool parseData(rapidxml::xml_node<>*root);
	std::string trim(const std::string&str);
	std::string decode(const std::string&encoding,const std::string&str);
	void uncompression(const std::string&compression,const std::string&decodeIDs);
};
#endif