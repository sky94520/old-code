#include "TowerPosEditorScene.h"
#include "TowerPos.h"
#include "PosLoadUtil.h"
#include "ui/CocosGUI.h"
TowerPosEditorScene::TowerPosEditorScene()
{
	m_configFileName[0] = "tollgate/towerPos_level_%d.plist";
	m_configFileName[1] = "tollgate/monsterPos_level_%d.plist";
	m_iCurLevel = 1;
	m_type = PosType::kTowerPos;
}
TowerPosEditorScene::~TowerPosEditorScene()
{
}
Scene*TowerPosEditorScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TowerPosEditorScene::create();
	scene->addChild(layer);
	return scene;
}
bool TowerPosEditorScene::init()
{
	if(!Layer::init())
		return false;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//初始化plist 
	loadConfigFile();
	//添加触屏监听
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch*,Event*){return true;};
	listener->onTouchEnded = [&](Touch*touch,Event*)
	{
		Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
		switch(m_type)
		{
		case PosType::kTowerPos:
			editTowerPos(pos);
			break;
		case PosType::kMonsterPos:
			editMonsterPos(pos);
			break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	//添加输出按钮
	ui::Button*saveBtn = ui::Button::create("button.png");
	Size saveBtnSize = saveBtn->getContentSize();
	saveBtn->setPosition(ccp(visibleSize.width - saveBtnSize.width/2,saveBtnSize.height));
	saveBtn->setTitleText("output");
	saveBtn->setTitleFontSize(20);
	this->addChild(saveBtn);
	saveBtn->addClickEventListener(CC_CALLBACK_1(TowerPosEditorScene::outputPosToPlistFile,this));
	//改变状态
	ui::Button*changeBtn = ui::Button::create("button.png");
	Size changeBtnSize = changeBtn->getContentSize();
	changeBtn->setPosition(ccp(visibleSize.width - changeBtnSize.width/2,changeBtnSize.height*2));
	changeBtn->setTitleText("Tower");
	changeBtn->setTitleFontSize(20);
	this->addChild(changeBtn);
	changeBtn->addClickEventListener([&,changeBtn](Ref*)
	{
		if(m_type == PosType::kTowerPos)
		{
			m_type = PosType::kMonsterPos;
			changeBtn->setTitleText("Monster");
		}
		else if(m_type == PosType::kMonsterPos)
		{
			m_type = PosType::kTowerPos;
			changeBtn->setTitleText("Tower");
		}
	});
	//下一关卡
	ui::Button*nextLevelBtn = ui::Button::create("button.png");
	Size nextLevelBtnSize = changeBtn->getContentSize();
	nextLevelBtn->setPosition(ccp(visibleSize.width - nextLevelBtnSize.width/2,3*nextLevelBtnSize.height));
	nextLevelBtn->setTitleText("Next Level");
	nextLevelBtn->setTitleFontSize(20);
	this->addChild(nextLevelBtn);
	nextLevelBtn->addClickEventListener([&](Ref*)
	{
		m_iCurLevel++;
		deleteAllPos();
		loadConfigFile();
	});
	//上一关卡
	ui::Button*preLevelBtn = ui::Button::create("button.png");
	Size preLevelBtnSize = preLevelBtn->getContentSize();
	preLevelBtn->setPosition(ccp(visibleSize.width - preLevelBtnSize.width/2,4*preLevelBtnSize.height));
	preLevelBtn->setTitleText("Pre Level");
	preLevelBtn->setTitleFontSize(20);
	this->addChild(preLevelBtn);
	preLevelBtn->addClickEventListener([&](Ref*)
	{
		if(m_iCurLevel == 1)
			return ;
		m_iCurLevel--;
		deleteAllPos();
		loadConfigFile();
	});
	return true;
}
void TowerPosEditorScene::editTowerPos(Point pos)
{
	auto existPos = findExistTowerPos(pos);
	if(existPos != NULL)
		deleteTowerPos(existPos);
	else
		createTowerPos(pos);
}
void TowerPosEditorScene::editMonsterPos(Point pos)
{
	auto existPos = findExistMonsterPos(pos);
	if(existPos != NULL)
		deleteMonsterPos(existPos);
	else
		createMonsterPos(pos);
}
PosBase*TowerPosEditorScene::findExistTowerPos(Point pos)
{
	for(int i=0;i< m_towerPosList.size();i++)
	{
		TowerPos* towerPos = (TowerPos*)m_towerPosList.at(i);
		if(towerPos->isClickMe(pos))
			return towerPos;
	}
	return NULL;
}
PosBase*TowerPosEditorScene::findExistMonsterPos(Point pos)
{
	for(int i=0;i< m_monsterPosList.size();i++)
	{
		if(m_monsterPosList.at(i)->isClickMe(pos))
			return m_monsterPosList.at(i);
	}
	return NULL;
}
void TowerPosEditorScene::createTowerPos(Point pos)
{
	TowerPos*tPos = TowerPos::create(pos,DEBUG_TEST);
	this->addChild(tPos);
	m_towerPosList.pushBack(tPos);
}
void TowerPosEditorScene::createMonsterPos(Point pos)
{
	PosBase*tPos = MonsterPos::create(pos,DEBUG_TEST);
	this->addChild(tPos);
	m_monsterPosList.pushBack(tPos);
}
void TowerPosEditorScene::deleteTowerPos(PosBase*existPos)
{
	this->removeChild(existPos); 
	m_towerPosList.eraseObject(existPos);
}
void TowerPosEditorScene::deleteMonsterPos(PosBase*existPos)
{
	this->removeChild(existPos); 
	m_monsterPosList.eraseObject(existPos);
}
void TowerPosEditorScene::deleteAllPos()
{
	//this->removeAllChildrenWithCleanup(true);
	//删除
	for(auto pos : m_towerPosList)
		this->removeChild(pos);
	for(auto pos : m_monsterPosList)
		this->removeChild(pos);
	//删除背景
	if(m_pBG !=NULL)
	{
		this->removeChild(m_pBG,true);
		m_pBG = NULL;
	}
	m_towerPosList.clear();
	m_monsterPosList.clear();
}
void TowerPosEditorScene::outputPosToPlistFile(Ref*)
{
	for(int i=0;i<2;i++)
	{
		int index = 1;
		ValueMap fileDataMap;
		//各个属性
		for(auto posBase : i==0?m_towerPosList:m_monsterPosList)
		{
			ValueMap data;
			data["x"] = (int) posBase->getPos().x;
			data["y"] = (int) posBase->getPos().y;
			fileDataMap[StringUtils::toString(index)] = Value(data);
			index ++;
		}
		FileUtils::getInstance()->writeToFile(fileDataMap,
			StringUtils::format(m_configFileName[i].c_str(),m_iCurLevel));
	}
}
void TowerPosEditorScene::loadConfigFile()
{
	//添加背景
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//加载背景图片
	std::string bgPath = StringUtils::format("tollgate/level_bg_%d.png",m_iCurLevel);
	if((m_pBG = Sprite::create(bgPath)) != NULL)
	{
		this->addChild(m_pBG,-1);
		m_pBG->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	}
	std::string towerPosName = StringUtils::format(m_configFileName[0].c_str(),m_iCurLevel);
	std::string monsterPosName = StringUtils::format(m_configFileName[1].c_str(),m_iCurLevel);
	//加载炮塔位置
	Vector<PosBase*> towerVec = PosLoadUtil::getInstance()->loadPosWithFile(
		towerPosName.c_str(),PosType::kTowerPos,this,m_iCurLevel,DEBUG_TEST);
	//加载怪物位置
	Vector<PosBase*> monsterVec = PosLoadUtil::getInstance()->loadPosWithFile(
		monsterPosName.c_str(),PosType::kMonsterPos,this,m_iCurLevel,DEBUG_TEST);
	m_towerPosList.pushBack(towerVec);
	m_monsterPosList.pushBack(monsterVec);
}
void TowerPosEditorScene::onDraw(const kmMat4 &transform,bool transformUpdated)
{
	kmGLPushMatrix();
	kmGLLoadMatrix(&transform);
	
	PosBase*prePos = NULL;
	//绘制线条
	for(auto nowPos : m_monsterPosList)
	{
		if(prePos != NULL)
			DrawPrimitives::drawLine(prePos->getPos(),nowPos->getPos());
		prePos = nowPos;
	}
	//DrawPrimitives::drawCircle(m_pos,MONSTER_RADIUS,360,20,false);
	glLineWidth(1);
	//结束绘制
	kmGLPopMatrix();
}
void TowerPosEditorScene::draw(Renderer*renderer,const kmMat4 &transform,uint32_t flags)
{
	if(DEBUG_TEST)
	{
		_customCommand.init(_globalZOrder);
		_customCommand.func = CC_CALLBACK_0(TowerPosEditorScene::onDraw,this,transform,flags);
		renderer->addCommand(&_customCommand);
	}
}
