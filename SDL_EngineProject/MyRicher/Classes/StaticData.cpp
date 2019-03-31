#include "StaticData.h"
#include "GameScene.h"

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
	bool ret = true;
	//读取文件
	m_plistMap = FileUtils::getInstance()->getValueMapFromFile(m_staticDataPath);

	return ret;
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

bool StaticData::split(Texture* texture,Rect* cap,const Size& size,const function<void (int,const vector<SpriteFrame*>& frames)>& callback)
{
	if (texture == nullptr)
		return false;
	//设置要切割的矩形
	Rect capInsect;
	if (cap == nullptr)
	{
		int w = 0,h = 0;
		texture->queryTexture(NULL,NULL,&w,&h);

		capInsect = Rect(0,0,w,h);
	}
	else
	{
		capInsect = *cap;
	}
	//获取行和列
	int row = int (capInsect.size.height / size.height);
	int col = int (capInsect.size.width / size.width);
	vector<SpriteFrame*> frames;
	SpriteFrame* frame = nullptr;
	//进行切割
	for (int i = 0;i < col;i++)
	{
		for (int j = 0;j < row;j++)
		{
			Rect rect;
			rect.origin.x = capInsect.origin.x + j * size.width;
			rect.origin.y = capInsect.origin.y + i * size.height;
			rect.size = size;

			frame = SpriteFrame::createWithTexture(texture,rect);
			frames.push_back(frame);
		}//回调函数
		callback(i,frames);
		frames.clear();
	}
	return true;
}

Animation* StaticData::getAnimationOfDirection(const string& playerName,Direction dir)
{
	auto format = this->getValueForKey("character_walking_animation_name_format")->asString();
	auto array = this->getValueForKey("character_dir_array")->asValueVector();
	auto nDir = static_cast<int>(dir);
	auto sDir = array.at(nDir).asString();
	//获取动画名称及动画
	auto animationName = StringUtils::format(format.c_str(),playerName.c_str(),sDir.c_str());
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);

	return animation;
}