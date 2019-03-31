#pragma once
#include<iostream>
#include<string>
#include<vector>

#include "TextureManager.h"
#include "base64.h"
#include "zlib.h"
#include "tinyxml.h"
#include "Level.h"
#include "TileLayer.h"

class LevelParser
{
    private:
    int m_tileSize;
    int m_width;
    int m_height;
    //解析图块集
    void parseTilesets(TiXmlElement* pTilesetRoot,
                       std::vector<Tileset>* pTilesets);
    //解析layer
    void parseTileLayer(TiXmlElement*pTileElement,
                        std::vector<Layer*> *pLayers,
                        const std::vector<Tileset>* pTilesets);
    //解析tmx所包含的图片，并加载
    void parseTextures(TiXmlElement*pTextureRoot);

    void parseObjectLayer(TiXmlElement*pObjectElement
                          ,std::vector<Layer*> *pLayer);
    public:
    Level*parseLevel(const char*levelFile);

};