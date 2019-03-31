#include "TMXLayer.h"
#include "base64.h"
#include "zlib.h"
TMXLayer::TMXLayer()
	:_layerName(""),_width(0),_height(0)
{
}
TMXLayer::~TMXLayer()
{
}
TMXLayer*TMXLayer::create(rapidxml::xml_node<>*root)
{
	auto layer = new TMXLayer();
	if(layer && layer->init(root))
		layer->autoRelease();
	else
		SDL_SAFE_DELETE(layer);
	return layer;
}
bool TMXLayer::init(rapidxml::xml_node<>*root)
{
	_layerName = root->first_attribute("name")->value();
	_width = atoi(root->first_attribute("width")->value());
	_height = atoi(root->first_attribute("height")->value());

	this->setName(_layerName);
	//data
	auto dataRoot = root->first_node("data");
	return parseData(dataRoot);
}
int TMXLayer::getTileGIDAt(const Point&tileCoordinate)const
{
	int x = (int)tileCoordinate.x;
	int y = (int)tileCoordinate.y;

	return _data[y][x];
}
std::string TMXLayer::getLayerName()const
{
	return _layerName;
}
bool TMXLayer::parseData(rapidxml::xml_node<>*root)
{
	std::string encoding = root->first_attribute("encoding")->value();
	std::string compression = root->first_attribute("compression")->value();
	std::string data = root->value();
	std::string decodeIDs;
	//判断encoding
	decodeIDs = this->decode(encoding,trim(data));
	this->uncompression(compression,decodeIDs);
	return true;
}
std::string TMXLayer::trim(const std::string&str)
{
	//分配一个同样大小的字符数组
	char*text = new char[str.length() + 1];
	for(int i=0;i<strlen(text);i++)
		text[i] = '\0';
	int i=0;//text指针
	for(int j=0;j < str.length();)
	{
		auto ch = str.at(j++);
		if(ch == '\t' || ch == '\n' || ch == '\r' || ch == ' ')
		{
			;
		}
		else
		{
			text[i++] = ch;
		}
	}
	text[i] = '\0';
	std::string trimstr = std::string(text);
	delete[] text;
	return trimstr;
}
std::string TMXLayer::decode(const std::string&encoding,const std::string&str)
{
	std::string decodeIDs;
	if(encoding == "base64")
	{
		decodeIDs = base64_decode(str);
	}
	return decodeIDs;
}
void TMXLayer::uncompression(const std::string&compression,const std::string&decodeIDs)
{
	if(compression == "zlib")
	{
		uLongf numGids = _width * _height*sizeof(int);
		//后300为空，不知道为什么
		auto data = std::vector<int>(numGids);
		uncompress((Bytef*)&data[0],&numGids,(const Bytef*)decodeIDs.c_str(),decodeIDs.size());
		//赋值
		std::vector<int> layerRow(_width);
		for(int i=0;i<_height;i++)
			_data.push_back(layerRow);
		for(int rows = 0;rows < _height;rows++)
		{
			for(int cols = 0;cols < _width;cols++)
			{
				_data[rows][cols] = data[rows * _width + cols];
			}
		}
	}
}