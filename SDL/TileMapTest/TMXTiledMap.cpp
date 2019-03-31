#include "TMXTiledMap.h"

TMXTiledMap::TMXTiledMap(std::string tmxPath,SDL_Renderer*ren)
{
    TiXmlDocument doc;
    //bind
    m_pRenderer = ren;
    //加载tmx
    if(!doc.LoadFile(tmxPath.c_str()))
    {
        std::cout<<"error:"<<doc.ErrorDesc()<<std::endl;
        return ;
    }
    //获得根节点
    TiXmlElement*pRoot = doc.RootElement();

    pRoot->Attribute("width",&m_width);
    pRoot->Attribute("height",&m_height);
    pRoot->Attribute("tilewidth",&m_tileSize);

 /*   std::cout<<"m_width "<<m_width<<std::endl;
    std::cout<<"m_height "<<m_height<<std::endl;
    std::cout<<"m_tileSize "<<m_tileSize<<std::endl;*/
    //parse the tilesets
    for(TiXmlElement*e = pRoot->FirstChildElement();e != NULL;e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("tileset"))
        {
            parseTilesets(e);
        }
    }
    //parse the data
    for(TiXmlElement*e = pRoot->FirstChildElement();e != NULL;e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("layer"))
        {
            parseTileLayer(e);
        }
    }
}
void TMXTiledMap::parseTilesets(TiXmlElement*pTilesetRoot)
{
    //create a tileset object
    Tileset tileset;
    pTilesetRoot->FirstChildElement()->Attribute("width",&tileset.width);
    pTilesetRoot->FirstChildElement()->Attribute("height",&tileset.height);

    pTilesetRoot->Attribute("firstgid",&tileset.firstGirdID);
    pTilesetRoot->Attribute("tilewidth",&tileset.tileWidth);
    pTilesetRoot->Attribute("tileheight",&tileset.tileHeight);
    pTilesetRoot->Attribute("spacing",&tileset.spacing);
    pTilesetRoot->Attribute("margin",&tileset.margin);

    tileset.name = pTilesetRoot->Attribute("name");

    tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);

    m_tilesets.push_back(tileset);
    //load texture在这里需要注意路径的修改
    std::string filePath = std::string("assets/") + pTilesetRoot->FirstChildElement()->Attribute("source");
    SDL_Texture*tex = IMG_LoadTexture(m_pRenderer,filePath.c_str());

    m_mapObjects[tileset.name] = tex;

    std::cout<<"\nfirstgid "<<tileset.firstGirdID<<std::endl;
    std::cout<<"tilewidth "<<tileset.tileWidth<<std::endl;
    std::cout<<"tileheight "<<tileset.tileHeight<<std::endl;
    std::cout<<"spacing "<<tileset.spacing<<std::endl;
    std::cout<<"margin "<<tileset.margin<<std::endl;
    std::cout<<"name "<<tileset.name<<std::endl;
    std::cout<<"numColumns "<<tileset.numColumns<<std::endl;
}
void TMXTiledMap::parseTileLayer(TiXmlElement*pTilesetRoot)
{
    std::string decodedIDs;
    TiXmlElement*pDataNode;

    for(TiXmlElement*e = pTilesetRoot->FirstChildElement();e != NULL;e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("data"))
        {
            pDataNode = e;
        }
    }
    for(TiXmlNode*e = pDataNode->FirstChild(); e != NULL; e = e->NextSibling())
    {
        //解码数据，并用string保存
        TiXmlText*text = e->ToText();
        std::string t = text->Value();
        decodedIDs = base64_decode(t);
    }
    //uncompress解压
    uLongf numGids = m_width * m_height * sizeof(int);
    std::vector<unsigned> gids(numGids);

    uncompress((Bytef*)&gids[0],&numGids,(const Bytef*)decodedIDs.c_str(),decodedIDs.size());
    std::vector<int> layerRow(m_width);
    //动态二维数组
    for(int j = 0; j < m_height;j++)
    {
        m_data.push_back(layerRow);
    }
    //为该二维数组赋值
    for(int rows = 0;rows < m_height;rows++)
    {
        for(int cols = 0;cols < m_width;cols++)
        {
            m_data[rows][cols] = gids[rows * m_width + cols];
        }
    }
    //检查数组直是否正确
    for(int rows = 0;rows < m_height;rows++)
    {
        for(int cols = 0;cols < m_width;cols++)
        {
            std::cout<<m_data[rows][cols]<<" ";
        }
        std::cout<<"\n";
    }
}

void TMXTiledMap::Draw()
{
    for(int i = 0;i < m_height;i++)
    {
        for(int j = 0;j < m_width;j++)
        {
            int id = m_data[i][j];
            //0代表无图块
            if(id == 0)
            {
                continue;
            }
            Tileset tileset = getTilesetByID(id);
            id--;

            drawTile(tileset.name,tileset.margin,tileset.spacing
                     ,j * m_tileSize,i * m_tileSize
                     ,m_tileSize,m_tileSize
                     ,(id - (tileset.firstGirdID - 1))/tileset.numColumns
                     ,(id - (tileset.firstGirdID - 1))%tileset.numColumns);
        }
    }
}
Tileset TMXTiledMap::getTilesetByID(int tileID)
{
    for(int i = 0;i < m_tilesets.size();i++)
    {
        /*这里的判断是如果tileID不在前m_tilesets.size()-1里面，
        就必定是最后一个*/
        if(i + 1 <= m_tilesets.size() - 1)
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
    std::cout<<"did not find tileset,rerturning empty tileset\n";
    Tileset t;
    return t;
}
void TMXTiledMap::drawTile(std::string id,int margin,int spacing,int x,int y,int width,int height,int currentRow,int currentFrame)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = margin + (spacing + width) * currentFrame;
    srcRect.y = margin + (spacing + height) * currentRow;

    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;

    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(m_pRenderer,m_mapObjects[id],&srcRect,&destRect,0,0,SDL_FLIP_NONE);
}
