#include "TileLayer.h"
#include "Game.h"
#include "TextureManager.h"

TileLayer::TileLayer(int tileSize,const std::vector<Tileset> &tilesets)
    :m_tileSize(tileSize),m_tilesets(tilesets),m_position(0,0),m_velocity(0,0)
{
	//多预存一个图块 + 1
    m_numColumns = (TheGame::Instance()->getGameWidth()/m_tileSize) + 1;
    m_numRow = (TheGame::Instance()->getGameHeight()/ m_tileSize);
}
void TileLayer::update()
{
    m_position += m_velocity;
    if(m_position.getX()/m_tileSize + m_numColumns >= m_mapWidth)
    {
        m_velocity.setX(0);
    }
    else
        m_velocity.setX(1);
}
void TileLayer::render()
{
    int x,y,x2,y2;

    x = m_position.getX()/m_tileSize;
    y = m_position.getY()/m_tileSize;

    x2 = int(m_position.getX()) % m_tileSize;
    y2 = int(m_position.getY()) % m_tileSize;
    //std::cout<<"x="<<x<<"\n";
    for(int i = 0; i < m_numRow; i++)
    {
        for(int j = 0; j < m_numColumns; j++)
        {
            int id = m_tileIDs[i + y][j + x];//+ x];

            if(id == 0)
                continue;
            Tileset tileset = getTilesetByID(id);
            id--;
            TheTextureManager::Instance()->drawTile(tileset.name,2,2,
                                                    (j * m_tileSize) - x2,(i * m_tileSize) - y2,
                                                    m_tileSize,m_tileSize,
                                                    ((id - (tileset.firstGirdID - 1))/tileset.numColumns)
                                                    ,((id - (tileset.firstGirdID - 1)) % tileset.numColumns));
        }
    }
}
Tileset TileLayer::getTilesetByID(int tileID)
{
    for(int i = 0; i < m_tilesets.size(); i++)
    {
        if( i + 1 <= m_tilesets.size() - 1)
        {
            if(tileID >= m_tilesets[i].firstGirdID && tileID < m_tilesets[i + 1].firstGirdID)
            {
                return m_tilesets[i];
            }
        }
        else
        {
            return m_tilesets[i];
        }
    }

    std::cout << "did not find tileset, returning empty tileset\n";
    Tileset t;
    return t;
}
