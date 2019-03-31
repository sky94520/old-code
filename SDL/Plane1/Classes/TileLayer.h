#pragma once#include<iostream>#include "Layer.h"#include "Vector2D.h"#include "Level.h"class TileLayer : public Layer{private:    //该屏幕能容纳的列数    int m_numColumns;    //该屏幕能容纳的行数    int m_numRow;    int m_tileSize;    //地图高度
    int m_mapHeight;
    //地图宽度
    int m_mapWidth;
    //坐标    Vector2D m_position;
    //速度    Vector2D m_velocity;    //    const std::vector<Tileset> &m_tilesets;
    std::vector<std::vector<int> > m_tileIDs;public:    TileLayer(int tileSize,const std::vector<Tileset> &tilesets);    virtual void update(Level*pLevel);    virtual void render();
    std::vector<std::vector<int> >& getTileIDs()
    {
    	return m_tileIDs;
    }    void setTileIDs(const std::vector<std::vector<int> > data)    {        m_tileIDs = data;    }    void setTileSize(int tileSize)    {        m_tileSize = tileSize;    }
    int getTileSize()
    {
    	return m_tileSize;
    }    Tileset getTilesetByID(int tileID);
    //设置地图宽高度
    void setMapWidth(int width)
    {
    	m_mapWidth = width;
    }
    void setMapHeight(int height)
    {
    	m_mapHeight = height;
    }
    Vector2D getPosition()
    {
    	return m_position;
    }};