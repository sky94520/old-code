#include "ThirdLayer.h"
#include "Text.h"

ThirdLayer::ThirdLayer()
{
}

ThirdLayer::~ThirdLayer()
{
	//BMFontConfiguration::removeFNTCache();
}


Scene* ThirdLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = ThirdLayer::create();
	
	scene->addChild(layer);
	return scene;
}

bool ThirdLayer::init()
{
	Director::getInstance()->getRenderer()->setRenderDrawColor(Color4B(0,255,255,255));

	Text* text = Text::create("fonts/1.fnt", 500, Color3B(0,0,0));
	text->setAnchorPoint(Point::ZERO);
	this->addChild(text);


	auto t = FileUtils::getInstance()->getDataFromFile("wenben.txt");
	text->wind(t, Size(400, 100), Color4B(), false);

	return true;
}