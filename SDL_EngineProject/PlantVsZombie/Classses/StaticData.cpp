#include "StaticData.h"
#include "Plant.h"
#include "Character.h"

StaticData*StaticData::m_pInstance = nullptr;

StaticData::StaticData()
{
	m_staticDataPath = STATIC_DATA_PATH;
}
StaticData::~StaticData()
{
}
StaticData*StaticData::getInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new StaticData();
		m_pInstance->init();
	}
	return m_pInstance;
}
void StaticData::purge()
{
	if(m_pInstance)
		SDL_SAFE_RELEASE_NULL(m_pInstance);
}
bool StaticData::init()
{
	bool bRet = true;
	//读取文件
	m_plistMap = FileUtils::getInstance()->getValueMapFromFile(m_staticDataPath);
	//读取分析card
	this->parseCard();
	//解析僵尸
	this->parseZombieCsvData();
	//读取植物数据
	this->parsePlantCsvData();

	return bRet;
}

Value *StaticData::getValueForKey(const string&key)
{
	auto iter = m_plistMap.find(key);

	if(iter != m_plistMap.end())
		return &iter->second;

	return nullptr;
}

Point StaticData::getPointForKey(const string&key)
{
	Point ret;

	auto value = this->getValueForKey(key);
	if(value->getType() != Value::Type::STRING)
		return ret;
	ret = PointFromString(value->asString());

	return ret;
}

TerrainType StaticData::convertStrToTerrainType(const string&sType)
{
	TerrainType type = TerrainType::None;
	//不区分大小写
	auto lowerType = StaticData::toLowerCase(sType);
	//草地
	if (lowerType == "lawn")
	{
		type = TerrainType::Lawn;
	}
	//水面
	else if (lowerType == "water")
	{
		type = TerrainType::Water;
	}
	//石头
	else if (lowerType == "stone")
	{
		type = TerrainType::Stone;
	}
	else if (lowerType == "lilypad")
	{
		type = TerrainType::LilyPad;
	}
	else if (lowerType == "flowerpot")
	{
		type = TerrainType::FlowerPot;
	}

	return type;
}

ActiveTime StaticData::convertStrToActiveType(const string&sType)
{
	ActiveTime type = ActiveTime::All;

	auto lowerType = StaticData::toLowerCase(sType);

	if (lowerType == "all")
		type = ActiveTime::All;
	else if (lowerType == "day")
		type = ActiveTime::Day;
	else if (lowerType == "night")
		type = ActiveTime::Night;

	return type;
}

PlantType StaticData::convertStrToPlantType(const string& sType)
{
	PlantType type = PlantType::Common;

	auto lowerType = StaticData::toLowerCase(sType);

	if (lowerType == "common")
		type = PlantType::Common;
	else if (lowerType == "nightplant")
		type = PlantType::NightPlant;
	else if (lowerType == "vessel")
		type = PlantType::Vessel;
	else if (lowerType == "defender")
		type = PlantType::Defender;

	return type;
}

Direction StaticData::convertStrToDir(const string&sType)
{
	Direction type = Direction::None;

	auto lowerType = StaticData::toLowerCase(sType);

	if (lowerType == "none")
		type = Direction::None;
	else if (lowerType == "left")
		type = Direction::Left;
	else if (lowerType == "right")
		type = Direction::Right;
	else if (lowerType == "all")
		type = Direction::All;

	return type;
}

string StaticData::toLowerCase(const string&text)
{
	string value;

	for (char ch:text)
	{
		char c = (char)tolower(ch);
		value.push_back(c);
	}

	return value;
}

CardStruct* StaticData::getCardStruct(const string&name)
{
	auto it = m_cardStructMap.find(name);

	if (it != m_cardStructMap.end())
		return &(it->second);

	return nullptr;
}

ZombieCsvStruct* StaticData::getZombieStructForName(const string&zombieName)
{
	auto it = m_zombieCsvMap.find(zombieName);

	if (it != m_zombieCsvMap.end())
		return &it->second;

	return nullptr;
}

PlantCsvStruct* StaticData::getPlantCsvStructForName(const string& plantName)
{
	auto it = m_plantCsvMap.find(plantName);

	if (it != m_plantCsvMap.end())
		return &it->second;

	return nullptr;
}

void StaticData::parseCard()
{
	//获取卡片路径
	auto path = STATIC_DATA_STRING("card_plist_path");

	auto valueMap = FileUtils::getInstance()->getValueMapFromFile(path);

	for (auto card : valueMap)
	{
		auto cardName = card.first;
		auto properties = card.second.asValueMap();

		CardStruct cardStruct;

		for (auto iter = properties.begin();iter != properties.end();iter++)
		{
			auto sName = iter->first;

			if (sName == "desc")
				cardStruct.desc = iter->second.asString();
			else if (sName == "worth")
				cardStruct.worth = iter->second.asInt();
			else if (sName == "CD")
				cardStruct.cd = iter->second.asFloat();
			else if (sName == "ready time")
				cardStruct.readyTime = iter->second.asFloat();
			else if (sName == "active")
			{
				auto sType = iter->second.asString();
				cardStruct.active = StaticData::convertStrToActiveType(sType);
			}
			//解析需要的地形		
			else if (sName == "needful terrain")
			{
				auto needfulTerrains = properties.at("needful terrain").asValueVector();
				for (auto sTerrain : needfulTerrains)
				{
					auto terrainType = StaticData::convertStrToTerrainType(sTerrain.asString());
					cardStruct.terrains.push_back(terrainType);
				}
			}
			else if (sName == "necessary item")
			{
				cardStruct.necessoryItem = iter->second.asString();
			}
		}
		m_cardStructMap.insert(make_pair(cardName,cardStruct));
	}
}

void StaticData::parseZombieCsvData()
{
	//获取路径
	auto path = STATIC_DATA_STRING("zombie_csv_path");
	auto text = FileUtils::getInstance()->getDataFromFile(path);

	string name;
	ZombieCsvStruct zombieStruct;

	auto splitColumn = [&zombieStruct,&name,this](int index,Value value)
	{
		switch (index)
		{
		case 0:name = value.asString();break;
		case 1:zombieStruct.speed = value.asFloat();break;
		case 2:zombieStruct.hp = value.asInt();break;
		case 3:zombieStruct.garnishry = value.asString();break;
		case 4://一行结束，保存到map中
			{
				zombieStruct.rect = RectFromString(value.asString(),' ');

				m_zombieCsvMap.insert(make_pair(name,zombieStruct));
			}break;
		}
	};
	auto splitRow = [&splitColumn](int index,Value value)
	{
		//去掉第一行和第二行
		if (index == 0 || index == 1)
			return;
		//再次进行切分
		StringUtils::split(value.asString(),",",splitColumn);
	};

	StringUtils::split(text,"\n",splitRow);
}

void StaticData::parsePlantCsvData()
{
	//获取路径
	auto path = STATIC_DATA_STRING("plant_csv_path");
	auto text = FileUtils::getInstance()->getDataFromFile(path);

	string name;
	PlantCsvStruct plantStruct;

	auto splitColumn = [&plantStruct,&name,this](int index,Value value)
	{
		switch (index)
		{
		case 0:name = value.asString();break;
		case 1:plantStruct.hp = value.asInt();break;
		case 2:plantStruct.cd = value.asFloat();break;
		case 3:
			{
				auto type = StaticData::convertStrToPlantType(value.asString());
				plantStruct.type = type;
			}break;
		case 4://一行结束
			{
				auto dir = StaticData::convertStrToDir(value.asString());
				plantStruct.dir = dir;

				m_plantCsvMap.insert(make_pair(name,plantStruct));
			}break;
		}
	};
	auto splitRow = [&splitColumn](int index,Value value)
	{
		//去掉第一行和第二行
		if (index == 0 || index == 1)
			return;
		//再次进行切分
		StringUtils::split(value.asString(),",",splitColumn);
	};

	StringUtils::split(text,"\r\n",splitRow);
}