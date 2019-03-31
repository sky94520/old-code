﻿#pragma once
    int m_mapHeight;
    //地图宽度
    int m_mapWidth;
    //坐标
    //速度

    std::vector<std::vector<int> >& getTileIDs()
    {
    	return m_tileIDs;
    }
    int getTileSize()
    {
    	return m_tileSize;
    }
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
    }