#include "LevelParser.h"

#include "ObjectLayer.h"
#include "GameObjectFactory.h"
#include "TextureManager.h"
#include "Player.h"

Level* LevelParser::parseLevel(const char*levelFile)
{
    //create a TinyXML document and loa the map xml
    TiXmlDocument levelDocument(levelFile);
    if(levelDocument.LoadFile())
    {
        std::cout<<"Loading tmx success:File Name "<<levelFile<<"\n";
    }
    else
    {
        throw std::runtime_error(levelDocument.ErrorDesc());
    }
    //create the level object
    Level*pLevel = new Level();
    //get the root node
    TiXmlElement*pRoot = levelDocument.RootElement();
    pRoot->Attribute("tilewidth",&m_tileSize);
    pRoot->Attribute("width",&m_width);
    pRoot->Attribute("height",&m_height);
    //we know that properties is the first child of the root
    TiXmlElement* pProperties = pRoot->FirstChildElement();
    // we must parse the textures needed for this level, which have been added to properties
    for(TiXmlElement* e = pProperties->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("property"))
        {
            parseTextures(e);
        }
    }
    //parse the tilesets
    for(TiXmlElement*e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("tileset"))
        {
            parseTilesets(e,pLevel->getTilesets());
        }
    }
    //parse any object layers
    for(TiXmlElement*e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("objectgroup"))
        {
            if(e->FirstChildElement()->Value() == std::string("object"))
            {
                parseObjectLayer(e,pLevel->getLayers(),pLevel);
            }
        }
        else if(e->Value() == std::string("layer"))
        {
            //if(e->FirstChildElement()->Value() == std::string("data"))
            {
                parseTileLayer(e,pLevel->getLayers(),pLevel->getTilesets(),pLevel->getCollisionLayers());
            }
        }
    }

    return pLevel;
}
void LevelParser::parseTilesets(TiXmlElement*pTilesetRoot,std::vector<Tileset>* pTilesets)
{
    //first add the tileset to texture manager
    ///TextureManager有错误处理，在此不做判断
    TheTextureManager::Instance()->load(
        std::string("assets/") + pTilesetRoot->FirstChildElement()->Attribute("source"),
        pTilesetRoot->Attribute("name"));
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

    pTilesets->push_back(tileset);
}
void LevelParser::parseTileLayer(TiXmlElement*pTileElement,
                                 std::vector<Layer*> *pLayers,
                                 const std::vector<Tileset>* pTilesets,
                                 std::vector<TileLayer*>* pCollisionLayer)
{
    TileLayer*pTileLayer = new TileLayer(m_tileSize,*pTilesets);
    //tile data sa
    std::vector<std::vector<int> > data;

    std::string decodedIDs;
    TiXmlElement*pDataNode;
    ///默认不是Collision Layer
    bool colliable = false;

    TiXmlElement*e = pTileElement->FirstChildElement();
    if(e->Value() == std::string("properties"))
    {
        std::cout<<"Parse Collision Layer:"<<pTileElement->Attribute("name")<<std::endl;
        colliable = true;
        e = e->NextSiblingElement();
        pDataNode = e;
    }
    else if(e->Value() == std::string("data"))
    {
        pDataNode = e;
        std::cout<<"Parse Tile Layer:"<<pTileElement->Attribute("name")<<std::endl;
    }

    for(TiXmlNode*e = pDataNode->FirstChild(); e != NULL; e = e->NextSibling())
    {
        TiXmlText*text = e->ToText();
        std::string t = text->Value();
        decodedIDs = base64_decode(t);
    }

    //uncompress zlib compression
    uLongf numGids = m_width * m_height * sizeof(int);
    std::vector<unsigned> gids(numGids);
    uncompress((Bytef*)&gids[0],&numGids,(const Bytef*)decodedIDs.c_str(),decodedIDs.size());

    std::vector<int> layerRow(m_width);

    for(int j = 0; j < m_height; j++)
    {
        data.push_back(layerRow);
    }
    for(int rows = 0; rows < m_height; rows++)
    {
        for(int cols = 0; cols < m_width; cols++)
        {
            data[rows][cols] = gids[rows * m_width + cols];
            std::cout<<data[rows][cols]<<" ";
        }
        std::cout<<std::endl;
    }
    pTileLayer->setTileIDs(data);
    //设置地图宽高度
    pTileLayer->setMapWidth(m_width);
    pTileLayer->setMapHeight(m_height);

    if(colliable == true)
    {
    	pCollisionLayer->push_back(pTileLayer);
    }
    pLayers->push_back(pTileLayer);
}
void  LevelParser::parseTextures(TiXmlElement*pTextureRoot)
{
    std::string path = std::string("assets/") + pTextureRoot->Attribute("value");
    TheTextureManager::Instance()->load(
        path,
        pTextureRoot->Attribute("name"));
}
void LevelParser::parseObjectLayer(TiXmlElement*pObjectElement,std::vector<Layer*>*pLayers,Level*pLevel)
{
    //pObjectElement 为 objectgroup
    //create an object layer
    ObjectLayer*pObjectLayer = new ObjectLayer();

    std::cout<<"Parse Object Layer:"<<pObjectElement->Attribute("name")<<"\n";

    for(TiXmlElement*e = pObjectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("object"))
        {
            std::cout<<"object:"<<e->Attribute("name")<<std::endl;

            int x,y,width,height,numFrames,callbackID = 0,animSpeed = 0;
            std::string textureID;
            ///type
            std::string type;
            //get the initial node values type,x and y
            e->Attribute("x",&x);
            e->Attribute("y",&y);
            type = e->Attribute("type");
            GameObject*pGameObject = TheGameObjectFactory::Instance()->create(type);

            //get the property values
            for(TiXmlElement*properties = e->FirstChildElement(); properties != NULL; properties = properties->NextSiblingElement())
            {
                if(properties->Value() == std::string("properties"))
                {
                    for(TiXmlElement*property = properties->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
                    {
                        if(property->Value() == std::string("property"))
                        {
                            if(property->Attribute("name") == std::string("numFrames"))
                            {
                                property->Attribute("value",&numFrames);
                            }
                            else if(property->Attribute("name") == std::string("textureHeight"))
                            {
                                property->Attribute("value",&height);
                            }
                            else if(property->Attribute("name") == std::string("textureID"))
                            {
                                textureID = property->Attribute("value");
                            }
                            else if(property->Attribute("name") == std::string("textureWidth"))
                            {
                                property->Attribute("value",&width);
                            }
                            else if(property->Attribute("name") == std::string("callbackID"))
                            {
                                property->Attribute("value",&callbackID);
                            }
                            else if(property->Attribute("name") == std::string("animSpeed"))
                            {
                                property->Attribute("value",&animSpeed);
                            }
                        }
                    }
                }
            }

            pGameObject->load(std::unique_ptr<LoaderParams>(new LoaderParams(x,y,width,height,textureID,numFrames,callbackID,animSpeed)));
            if(type == std::string("Player"))
                pLevel->setPlayer(dynamic_cast<Player*>(pGameObject));
            pObjectLayer->getGameObjects()->push_back(pGameObject);
        }//end object
    }
    pLayers->push_back(pObjectLayer);
}
