#ifndef __Level_H__
#define __Level_H__

#include<iostream>
#include<string>
#include<vector>

#include "Layer.h"
class Player;
class TileLayer;

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
    ///Collision layer
    std::vector<TileLayer*> m_pCollisionLayer;
    ///save player
    Player*m_player;
private:
    Level();
    friend class LevelParser;
public:

    ~Level() {}

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
    Player* getPlayer()
    {
        return m_player;
    }
    void setPlayer(Player* pPlayer)
    {
        m_player = pPlayer;
    }
    std::vector<TileLayer*>* getCollisionLayers() { return &m_pCollisionLayer; }

    const std::vector<TileLayer*>& getCollidableLayers() { return m_pCollisionLayer; }
};
#endif
