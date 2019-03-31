#include "HelloWorldScene.h"
#include "SDL_gfx.h"

HelloWorld::HelloWorld()
	:m_elpased(0.f)
{
}
HelloWorld::~HelloWorld()
{
}
Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	Director::getInstance()->getRenderer()->setRenderDrawColor(0,255,255,255);
	Director::getInstance()->getSpriteFrameCache()->addSpriteFramesWithFile("image/resources.xml");

	MoveBy*m1 = MoveBy::create(6,Point(600,0));
	MoveBy*m2 = MoveBy::create(6,Point(600,0));
	Speed*speed = Speed::create(m2,0.5);
	speed->setTag(1);

	Sprite*s1 = Sprite::createWithSpriteFrameName("item1_00.png");
	Sprite*s2 = Sprite::createWithSpriteFrameName("item1_00.png");
	s2->setTag(1);
	s1->setPosition(100,100);
	s2->setPosition(100,130);
	this->addChild(s1);
	this->addChild(s2);

	s1->runAction(m1);
	s2->runAction(speed);

	this->scheduleUpdate();
	//test
	LabelDotChar*label = LabelDotChar::create("hello,I want 3 eggs,\ncan you bring them to me?",2,Color3B(0,0,0));
	auto size = label->getContentSize();
	label->setPosition(300,300);
	this->addChild(label);
	return true;
}
void HelloWorld::update(float dt)
{
/*	SDL_Renderer*renderer = Director::getInstance()->getRenderer()->getSDL_Renderer();
	Sint16 vx[] = {100,200,300,400};
	Sint16 vy[] = {100,50,150,100};
	Color4B color = Director::getInstance()->getRenderer()->getRenderDrawColor();*/
	auto node = this->getChildByTag(1);
	Speed* speed = dynamic_cast<Speed*>(node->getActionByTag(1));
	if(speed)
	{
		auto s = speed->getSpeed() + 0.01;
		speed->setSpeed(s);
	}
}
void HelloWorld::callback(Object*sender)
{
	ui::Button*btn = dynamic_cast<ui::Button*>(sender);
	//btn->setTouchEnabled(false);
	printf("hello");
}
void HelloWorld::touchCallback(Object*sender,ui::TouchEventType type)
{
	printf("%d\n",type);
}
void HelloWorld::checkBoxCallback(Object*sender,ui::CheckBox::EventType type)
{
	//printf("%d\t",type);
	if(type == ui::CheckBox::EventType::UNSELECTED)
	{
		auto widget = dynamic_cast<ui::Widget*>(sender);
		widget->setTouchEnabled(false);
	}
}
void HelloWorld::radioButtonCallback(Object*sender,ui::RadioButton::EventType type)
{
	printf("dan xuan\n");
}
void HelloWorld::radioButtonGroupCallback(ui::RadioButton*r,int index,ui::RadioButtonGroup::EventType type)
{
	printf("%d:%d",index,type);
}
void HelloWorld::createLabelAtlas(const string&text,const string&charMapFle,int itemWidth,int itemHeight,unsigned int startChar)
{
	Renderer*renderer = Director::getInstance()->getRenderer();
	
	//获取图片总路径
	auto fullPath = FileUtils::getInstance()->fullPathForFilename(charMapFle);
	if(fullPath.empty())
		return;
	//读取图片
	Texture*texture = renderer->imgLoadTexture(fullPath.c_str());
	int textureWidth,textureHeight;
	texture->queryTexture(nullptr,nullptr,&textureWidth,&textureHeight);
	int rowItemsNum = textureWidth/itemWidth;
	//每一列的字符数
	int columnItemsNum = textureHeight/itemHeight;

	int width = text.size()*itemWidth;
	int height = itemHeight;
	//创建空的texture
	Texture*bg = renderer->createTexture(SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,width,height);
	bg->setTextureBlendMode(SDL_BLENDMODE_BLEND);
	//设置bg为当前渲染目标
	renderer->setRenderTarget(bg);
	//渲染
	for(auto i=0;i<text.size();i++)
	{
		int ch = text.at(i);
		if(ch < startChar)
			continue;
		SDL_Rect srcRect = {(ch-startChar)%rowItemsNum *itemWidth,(ch-startChar)/rowItemsNum * itemHeight,itemWidth,itemHeight};
		SDL_Rect destRect = {i*itemWidth,0,itemWidth,itemHeight};

		renderer->renderCopy(texture,&srcRect,&destRect);
	}
	//设置为默认渲染目标
	renderer->setRenderTarget(nullptr);

	//创建Sprite
	Sprite*sprite = Sprite::createWithTexture(bg);
	sprite->setPosition(200,200);
	this->addChild(sprite);
}