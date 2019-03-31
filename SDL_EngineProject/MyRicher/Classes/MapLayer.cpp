#include "MapLayer.h"

MapLayer::MapLayer()
{
}

MapLayer::~MapLayer()
{
}

MapLayer* MapLayer::createWithLevel(const string& levelName)
{
	auto layer = new MapLayer();

	if (layer && layer->initWithLevel(levelName))
		layer->autoRelease();
	else
		SDL_SAFE_DELETE(layer);

	return layer;
}

bool MapLayer::init()
{
	return true;
}

bool MapLayer::initWithLevel(const string& levelName)
{
	m_pTiledMap = TMXTiledMap::create(levelName);

	this->addChild(m_pTiledMap);

	return true;
}

TMXObjectGroup* MapLayer::getObjectGroup()const
{
	return m_pTiledMap->getObjectGroup("object layer");
}