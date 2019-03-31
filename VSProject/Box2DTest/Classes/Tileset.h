#ifndef __SDL_Tileset_H__
#define __SDL_Tileset_H__
#include<string>
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
public:
	Tileset();
	~Tileset();
	static Tileset*create(rapidxml::xml_node<>*root);
	bool init(rapidxml::xml_node<>*root);
private:
	void parseImage(rapidxml::xml_node<>*imageRoot);
	void parseTile(rapidxml::xml_node<>*tileRoot);
};
#endif