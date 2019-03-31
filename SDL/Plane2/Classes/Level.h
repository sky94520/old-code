#ifndef __Level_H__
#define __Level_H__

#include<iostream>
#include<string>
#include<vector>

#include "Layer.h"

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
class Level
{
  private:
    //保存TiledLayer可能会用到的图块属性
    std::vector<Tileset> m_tilesets;
    //暂时包含TiledLayer和ObjectLayer
    std::vector<Layer*> m_layers;

  private:
    Level();
    friend class LevelParser;
  public:

    ~Level(){}

    void update();
    void render();
/*±ãÓÚ¸³Öµ*/
    std::vector<Tileset>* getTilesets()
    {
        return &m_tilesets;
    }
    std::vector<Layer*>* getLayers()
    {
        return &m_layers;
    }
    void output()
    {
        std::cout<<"Level\ntileset"<<std::endl;
        for(int i = 0;i < m_tilesets.size();i++)
        {
            std::cout<<m_tilesets[i].firstGirdID<<std::endl;
            std::cout<<m_tilesets[i].tileWidth<<std::endl;
            std::cout<<m_tilesets[i].tileHeight<<std::endl;
            std::cout<<m_tilesets[i].spacing<<std::endl;
            std::cout<<m_tilesets[i].margin<<std::endl;
            std::cout<<m_tilesets[i].width<<std::endl;
            std::cout<<m_tilesets[i].height<<std::endl;
            std::cout<<m_tilesets[i].numColumns<<std::endl;
            std::cout<<m_tilesets[i].name<<std::endl;
        }
    }
};
#endif
