#include "ShopLayer.h"
#include "MapLayer.h"
#include "LuaEngine.h"

ShopLayer::ShopLayer()
	:m_bShowingShop(false),m_pShop(nullptr)
	,m_pBuyTarget(nullptr),m_bCanBuy(false)
	,m_pMapLayer(nullptr)
{
}
ShopLayer::~ShopLayer()
{
	m_pMapLayer = nullptr;
}
bool ShopLayer::init()
{
	//������Ʒ�ű�
	LuaEngine::getInstance()->dofile("item.lua");

	m_pShop = CSLoader::createNode("MainScene.csb");
	this->addChild(m_pShop);
	//��ȡ�̵갴ť �����¼�
	auto shopBtn = dynamic_cast<Button*>(m_pShop->getChildByName("button_shop"));
	shopBtn->addClickEventListener(CC_CALLBACK_1(ShopLayer::showShop,this));
	//��ȡ�������� �����¼� todo
	auto panelShop = m_pShop->getChildByName("panel_shop");
	Widget*scrollViewShop = dynamic_cast<Widget*>(panelShop->getChildByName("scrollview_shop"));

	auto children = scrollViewShop->getChildren();
	for(int i=0;i<children.size();i++)
	{
		//Ϊ����ÿ����Ʒ���������¼�
		Layout*shopItem = dynamic_cast<Layout*>(children.at(i));
		shopItem->addTouchEventListener(CC_CALLBACK_2(ShopLayer::buy,this));
		//��ȡ�ű���Ӧ����Ʒ����
		std::string item = StringUtils::format("item%i",i+1);
		auto itemName = LuaEngine::getInstance()->getStringFromTable(item.c_str(),"name");
		auto itemNormalImage = LuaEngine::getInstance()->getStringFromTable(item.c_str(),"normalImage");
		auto itemUnusableImage = LuaEngine::getInstance()->getStringFromTable(item.c_str(),"unusableImage");
		auto itemPrice = LuaEngine::getInstance()->getStringFromTable(item.c_str(),"price");
		//���Ķ�Ӧ����Ʒ��
		Text*csbItemName = dynamic_cast<Text*>(shopItem->getChildByName("item_name"));
		ImageView*csbItemPic = dynamic_cast<ImageView*>(shopItem->getChildByName("pic"));
		//��ȡ�۸�
		auto csbItemPriceParent = shopItem->getChildByName("price");
		auto csbItemPrice = dynamic_cast<Text*>(csbItemPriceParent->getChildByName("price"));

		csbItemName->setText(itemName);
		csbItemPic->loadTexture(itemNormalImage);
		csbItemPrice->setText(itemPrice);
		//Ϊ����帳ֵ
		shopItem->setUserObject(String::create(item));
	}
	return true;
}
void ShopLayer::showShop(Ref*sender)
{
	//cocostudio::GUIReader::getInstance()->widgetFromJsonFile("");
	//��ȡ�̵����
	auto shop_panel = dynamic_cast<Widget*>(m_pShop->getChildByName("panel_shop"));
	//��ʾ�̵�
	if(m_bShowingShop == false)
	{
		m_bShowingShop = true;
		//��ʾ����
		MoveBy*move = MoveBy::create(1.f,Point(300.f,0.f));
		shop_panel->runAction(EaseElasticOut::create(move));
	}
	else
	{
		m_bShowingShop = false;
		MoveBy*move = MoveBy::create(1.f,Point(-300.f,0.f));
		shop_panel->runAction(EaseElasticOut::create(move));
	}
}
//Ref Layout
void ShopLayer::buy(Ref*sender,Widget::TouchEventType type)
{
	Layout*shopItem = dynamic_cast<Layout*>(sender);
	//��ø�������Ʒ
	String*item = (String*)shopItem->getUserObject();

	ImageView*pic = dynamic_cast<ImageView*>(shopItem->getChildByName("pic"));
	Text*price = dynamic_cast<Text*>(shopItem->getChildByName("price"));

	Sprite*bgSprite = m_pMapLayer->getBgSprite();
	Point originPos = m_pMapLayer->getOriginalPosition();
	TMXTiledMap*tiledMap = m_pMapLayer->getTMXTiledMap();

	switch(type)
	{
		//�Ŵ�ѡ����Ʒ
	case Widget::TouchEventType::BEGAN:
		pic->runAction(EaseElasticInOut::create( ScaleTo::create(0.1f, 1.5), 0.2f));
		break;
	case Widget::TouchEventType::MOVED:
		//��ʱ����һ����Ʒ
		if(m_pBuyTarget == nullptr)
		{
			auto itemNormalImage = LuaEngine::getInstance()->getStringFromTable(item->getCString(),"normalImage");

			m_pBuyTarget = Sprite::create(itemNormalImage);
			m_pBuyTarget->setScale(1.f);
			m_pBuyTarget->setAnchorPoint(Point(0.5f,0.15f));

			bgSprite->addChild(m_pBuyTarget);
		}
		//�ƶ�
		else
		{
			Point pos;
			pos.x = (shopItem->getTouchMovePosition().x - originPos.x)/bgSprite->getScale();
			pos.y = (shopItem->getTouchMovePosition().y - originPos.y)/bgSprite->getScale();
			m_pBuyTarget->setPosition(pos);
			this->moveCheck(pos,item);
		}
		break;
	case Widget::TouchEventType::ENDED:
	{	
		pic->runAction(EaseElasticInOut::create(ScaleTo::create(0.1f, 1), 0.2f));
		if(m_pBuyTarget)
		{
			bgSprite->removeChild(m_pBuyTarget,true);
			m_pBuyTarget = nullptr;
		}
	}break;
	case Widget::TouchEventType::CANCELED:
	{
		//��Ӧ��ͼ��GID
		auto gid = LuaEngine::getInstance()->getIntegerFromTable(item->getCString(),"tileGID");

		pic->runAction(EaseElasticInOut::create(ScaleTo::create(0.1f, 1), 0.2f));
		if(m_pBuyTarget)
		{
			bgSprite->removeChild(m_pBuyTarget,true);
			m_pBuyTarget = nullptr;
		}
		//ȥ��ָʾ
		tiledMap->getLayer("tipsLayer")->removeTileAt(m_prePos);

		if(m_bCanBuy == false)
			break;
		//��ȡ����λ��
		Point endPos;
		endPos.x = (shopItem->getTouchEndPos().x-originPos.x)/bgSprite->getScale();
		endPos.y = (shopItem->getTouchEndPos().y - originPos.y)/bgSprite->getScale();
		//�ڶ�Ӧλ��������Ƭ

		tiledMap->getLayer("goodsLayer")->setTileGID(gid,convertToTiledCoord(endPos));
	}
		break;
	}
}
Point ShopLayer::convertToTiledCoord(const Point&position)
{
	auto tiledMap = m_pMapLayer->getTMXTiledMap();

	//��ͼͼ�����
	auto mapSize = tiledMap->getMapSize();
	//��ǰ�����£�ÿ��ͼ��Ĵ�С
	auto tileSize = Size(tiledMap->getBoundingBox().size.width/mapSize.width,
		tiledMap->getBoundingBox().size.height/mapSize.height);
	//ת������Ƭ����
	int posx = mapSize.height - position.y / tileSize.height + position.x / tileSize.width - mapSize.width / 2;
	int posy = mapSize.height - position.y / tileSize.height - position.x / tileSize.width + mapSize.width / 2;
	return Point(posx,posy);
}
Point ShopLayer::convertToScreenCoord(const Point&position)
{
	auto tiledMap = m_pMapLayer->getTMXTiledMap();

	auto mapSize = tiledMap->getMapSize();
	auto tileSize = tiledMap->getTileSize();

	auto tileWidth = tiledMap->getBoundingBox().size.width/mapSize.width;
	auto tileHeight = tiledMap->getBoundingBox().size.height/mapSize.height;

	auto variable1 = (position.x + mapSize.width / 2 - mapSize.height) * tileWidth * tileHeight ;
    auto variable2 = (-position.y + mapSize.width / 2 + mapSize.height) * tileWidth * tileHeight ;

    int posx = (variable1 + variable2) / 2 / tileHeight;
    int posy = (variable2 - variable1) / 2 / tileWidth;

    return Point(posx, posy);
}
void ShopLayer::moveCheck(const Point&position,String*item)
{
	auto normalImage = LuaEngine::getInstance()->getStringFromTable(item->getCString(),"normalImage");
	auto unusableImage = LuaEngine::getInstance()->getStringFromTable(item->getCString(),"unusableImage");

	auto tiledMap = m_pMapLayer->getTMXTiledMap();

	auto mapSize = tiledMap->getMapSize();
	auto tilePos = this->convertToTiledCoord(position);
	m_bCanBuy = false;
	m_prePos = m_curPos;
	//��ȡֵ��Χ��
	if(tilePos.x >= 0 && tilePos.x < mapSize.width && tilePos.y >= 0 && tilePos.y < mapSize.height)
	{
		m_curPos = tilePos;

		int gid = tiledMap->getLayer("goodsLayer")->getTileGIDAt(tilePos);
		if(gid == 0)
			m_bCanBuy = true;
		auto screenPos = this->convertToScreenCoord(tilePos);

		m_pBuyTarget->setPosition(screenPos);

		if(m_prePos != m_curPos)
		{
			tiledMap->getLayer("tipsLayer")->removeTileAt(m_prePos);
			tiledMap->getLayer("tipsLayer")->setTileGID(17,m_curPos);
		}
	}
	else
	{
		tiledMap->getLayer("tipsLayer")->removeTileAt(m_prePos);
	}
	if(m_bCanBuy == false)
		m_pBuyTarget->setTexture(unusableImage);
	else
		m_pBuyTarget->setTexture(normalImage);

	
}
