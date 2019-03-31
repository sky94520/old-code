#include "PlantFactory.h"
#include "SunFlower.h"
#include "FlowerPot.h"
#include "LilyPad.h"
#include "Chomper.h"
#include "Squash.h"
#include "Jalapeno.h"
#include "Cattail.h"
#include "Pumpkin.h"

#include "Peashooter.h"
#include "Repeater.h"
#include "Threepeater.h"
#include "GatlingPea.h"
#include "SplitPea.h"
#include "FirePeashooter.h"

#include "PotatoMine.h"
#include "Cabbage.h"
#include "WallNut.h"
#include "SnowPea.h"
#include "TallNut.h"
#include "FumeShroom.h"
#include "IceShroom.h"
#include "Cornpult.h"
#include "PuffShroom.h"
#include "ScaredyShroom.h"
#include "SeaShroom.h"
#include "DoomShroom.h"
#include "Magnetshroom.h"
#include "SunShroom.h"
#include "HypnoShroom.h"
#include "Torchwood.h"
#include "StaticData.h"
#include "NameDef.h"

PlantFactory::PlantFactory()
{
}

PlantFactory::~PlantFactory()
{
}

bool PlantFactory::init()
{
	return true;
}

Plant* PlantFactory::makePlant(const string& name)
{
	Plant*plant = nullptr;
	//获取植物所对应的结构体
	auto plantCsvStruct = StaticData::getInstance()->getPlantCsvStructForName(name);
	//没找到对应的植物，直接退出
	if (plantCsvStruct == nullptr)
		return nullptr;
	//创建植物
	if (name == SUNFLOWER_NAME)
	{
		plant = SunFlower::create(name);
	}
	else if (name == TWINSUNFLOWER_NAME)
	{
		plant = TwinSunflower::create(name);
	}
	else if (name == FLOWERPOT_NAME)
	{
		plant = FlowerPot::create(name);
	}
	else if (name == LILYPAD_NAME)
	{
		plant = LilyPad::create(name);
	}
	else if (name == CHOMPER_NAME)
	{
		auto temp = Chomper::create(name);
		//设置额外属性
		temp->setDamage(1800);
		temp->setScope(140.f);

		plant = temp;
	}
	else if (name == SQUASH_NAME)
	{
		auto temp = Squash::create(name);
		//设置额外属性
		temp->setDamage(1800);
		temp->setScope(120.f);

		plant = temp;
	}
	else if (name == JALAPENO_NAME)
	{
		auto temp = Jalapeno::create(name);
		//设置额外属性
		temp->setDamage(1800);

		plant = temp;
	}
	else if (name == POTATOMINE_NAME)
	{
		auto temp = PotatoMine::create(name);
		temp->setDamage(1800);

		plant = temp;
	}
	else if (name == TORCHWOOD_NAME)
	{
		plant = Torchwood::create(name);
	}
	else if (name == CATTAIL_NAME)
	{
		auto temp = Cattail::create(name);
		temp->setDamage(20);

		plant = temp;
	}
	else if (name == PUMPKIN_NAME)
	{
		plant = Pumpkin::create(name);
	}
	//豌豆类植物
	else if (name == PEASHOOTER_NAME || name == REPEATER_NAME 
		|| name == THREEPEATER_NAME || name == GATLINPEA_NAME
		|| name == FIRE_PEASHOOTER_NAME || name == SNOWPEA_NAME
		|| name == SPLITPEA_NAME)
	{
		plant = this->makePea(name);
	}
	//坚果类植物
	else if (name == WALLNUT_NAME || name == TALLNUT_NAME)
	{
		plant = this->makeNut(name);
	}
	//投掷类植物
	else if (name == CABBAGE_NAME || name == CORNPULT_NAME)
	{
		plant = this->makeCatapult(name);
	}
	//夜晚植物
	else if (name == FUMESHROOM_NAME || name == ICESHROOM_NAME
		|| name == PUFFSHROOM_NAME || name == SEASHROOM_NAME
		|| name == SCAREDYSHROOM_NAME || name == DOOM_SHROOM_NAME
		|| name == MAGNETSHROOM_NAME || name == SUN_SHROOM_NAME
		|| name == HYPNOSHROOM_NAME)
	{
		plant = this->makeNightPlant(name);
	}
	//设置各种属性
	plant->setHitPoint(plantCsvStruct->hp);
	plant->setMaxHitPoint(plantCsvStruct->hp);
	plant->setColdDownTime(plantCsvStruct->cd);
	plant->setPlantType(plantCsvStruct->type);
	plant->setDir(plantCsvStruct->dir);

	return plant;
}

Pea* PlantFactory::makePea(const string& name)
{
	int bulletNum = 1;
	int damage = 0;

	Pea*plant = nullptr;

	if (name == PEASHOOTER_NAME)
	{
		plant = Peashooter::create(name);
		damage = 20;
	}
	else if (name == REPEATER_NAME)
	{
		plant = Repeater::create(name);
		bulletNum = 2;
		damage = 20;
	}
	else if (name == SPLITPEA_NAME)
	{
		plant = SplitPea::create(name);
		bulletNum = 1;
		damage = 20;
	}
	else if (name == THREEPEATER_NAME)
	{
		plant = Threepeater::create(name);

		bulletNum = 3;
		damage = 20;
	}
	else if (name == GATLINPEA_NAME)
	{
		plant = GatlingPea::create(name);

		bulletNum = 4;
		damage = 20;
	}
	else if (name == SPLITPEA_NAME)
	{
		plant = SplitPea::create(name);
		damage = 20;
	}
	else if (name == FIRE_PEASHOOTER_NAME)
	{
		plant = FirePeashooter::create(name);
		damage = 40;
	}
	else if (name == SNOWPEA_NAME)
	{
		plant = SnowPea::create(name);
		damage = 20;
	}
	plant->setBulletNumber(bulletNum);
	plant->setDamage(damage);

	return plant;
}

WallNut* PlantFactory::makeNut(const string& name)
{
	WallNut*plant = nullptr;

	if (name == WALLNUT_NAME)
	{
		plant = WallNut::create(name);
	}
	else if (name == TALLNUT_NAME)
	{
		plant = TallNut::create(name);
	}
	return plant;
}

Catapult* PlantFactory::makeCatapult(const string&name)
{
	Catapult*plant = nullptr;
	int damage = 0;

	if (name == CABBAGE_NAME)
	{
		plant = Cabbage::create(name);
		damage = 40;
	}
	else if (name == CORNPULT_NAME)
	{
		plant = Cornpult::create(name);
		damage = 20;
	}
	plant->setDamage(damage);

	return plant;
}

NightPlant*PlantFactory::makeNightPlant(const string& name)
{
	NightPlant*plant = nullptr;

	if (name == FUMESHROOM_NAME)
	{
		auto temp = FumeShroom::create(name);
		//设置额外属性
		temp->setDamage(20);
		temp->setAttackScope(400.f);

		plant = temp;
	}
	else if(name == ICESHROOM_NAME)
	{
		auto temp = IceShroom::create(name);
		temp->setDamage(20);

		plant = temp;
	}
	else if (name == PUFFSHROOM_NAME)
	{
		auto temp = PuffShroom::create(name);
		//设置额外属性
		temp->setDamage(20);
		temp->setAttackScope(240.f);

		plant = temp;
	}
	else if (name == SEASHROOM_NAME)
	{
		auto temp = SeaShroom::create(name);
		//设置额外属性
		temp->setDamage(20);
		temp->setAttackScope(240.f);

		plant = temp;
	}
	else if (name == SCAREDYSHROOM_NAME)
	{
		auto temp = ScaredyShroom::create(name);
		//设置额外属性
		temp->setDamage(20);

		plant = temp;
	}
	else if (name == DOOM_SHROOM_NAME)
	{
		auto temp = DoomShroom::create(name);
		//设置额外属性
		temp->setDamage(1800);

		plant = temp;
	}
	else if (name == MAGNETSHROOM_NAME)
	{
		auto temp = Magnetshroom::create(name);
		//设置额外属性
		temp->setScope(Size(300.f,300.f));

		plant = temp;
	}
	else if (name == SUN_SHROOM_NAME)
	{
		auto temp = SunShroom::create(name);
		//设置额外属性
		temp->setGrowUpTimeLeft(120.f);

		plant = temp;
	}
	else if (name == HYPNOSHROOM_NAME)
	{
		plant = HypnoShroom::create(name);
	}

	return plant;
}