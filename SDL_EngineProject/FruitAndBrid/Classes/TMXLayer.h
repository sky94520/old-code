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
	//�����Ÿ�layer��ѹ���������
	std::vector<std::vector<int> > _data;
	int _width;
	int _height;
public:
	TMXLayer();
	~TMXLayer();
	static TMXLayer*create(rapidxml::xml_node<>*root);
	bool init(rapidxml::xml_node<>*root);
	//���������ȡ��Ӧgid
	//pos param Ϊ��ͼ��Ӧ����
	int getTileGIDAt(const Point&tileCoordinate)const;

	std::string getLayerName()const;
private:
	bool parseData(rapidxml::xml_node<>*root);
	std::string trim(const std::string&str);
	std::string decode(const std::string&encoding,const std::string&str);
	void uncompression(const std::string&compression,const std::string&decodeIDs);
};
#endif