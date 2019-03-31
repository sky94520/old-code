#ifndef __TMXTiledMap_H__
#define __TMXTiledMap_H__

#include<iostream>
#include<vector>
#include<string>
#include<map>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "tinyxml.h"
#include "base64.h"
#include "zlib.h"
/*图块集*/
struct Tileset
{
    int firstGirdID;
    int tileWidth;
    int tileHeight;
    int spacing;
    int margin;
    int width;
    int height;
    int numColumns;
    std::string name;
};
class TMXTiledMap
{
  private:
    //保存图块集
    std::vector<Tileset> m_tilesets;
    //保存数据> >中间最好有空格
    std::vector<std::vector<int> > m_data;
    //tmx文件的宽 高/个数,在render时用的到
    int m_width;
    int m_height;
    //tileset size
    int m_tileSize;
    //save picture
    std::map<std::string,SDL_Texture*> m_mapObjects;
    //renderer
    SDL_Renderer*m_pRenderer;
  private:
    //解析layer中的data
    void parseTileLayer(TiXmlElement*pRoot);
    //解析tileset
    void parseTilesets(TiXmlElement*pTilesetRoot);
    //根据id获得相应的图块集
    Tileset getTilesetByID(int tileID);
    //内部的draw，封装了SDL_RenderCopyEx
    void drawTile(std::string id,int margin,int spacing,int x,int y,int width,int height,int currentRow,int currentFame);
  public:
    //解析，并绑定renderer
    TMXTiledMap(std::string tmxPath,SDL_Renderer*ren);
    void Draw();
};
#endif
