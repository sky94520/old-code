#include "Text.h"

Text::Text()
	:m_pConfiguration(nullptr)
	,m_nWidth(0)
	,m_fontSize(15)
	,m_nWindIndex(0)
	,m_elapsed(0.f)
{
}

Text::~Text()
{
	SDL_SAFE_RELEASE(m_pConfiguration);
}

Text* Text::create(const string& fontFile, int width, const Color3B& color)
{
	auto text = new Text();

	if (text && text->init(fontFile, width, color))
		text->autorelease();
	else
		SDL_SAFE_DELETE(text);

	return text;
}

bool Text::init(const string& fontFile, int width, const Color3B& color)
{
	m_pConfiguration = BMFontConfiguration::createWithFile(fontFile);
	SDL_SAFE_RETAIN(m_pConfiguration);

	m_nWidth = width;
	m_color = color;

	return true;
}

float Text::wind(const string& text, const Size& size, const Color4B& color, bool run)
{
	if (text.empty())
		return 0.f;

	int nextFontPositionX = 0;  //下一个字的横向绘制位置  
	int nextFontPositionY = 0;   //下一个字的纵向绘制位置 
	unsigned int quantityOfLines = 1;
	unsigned int totalHeight = 0;//字符串的总高度
	int longestLine = 0;        // 最长的一行的宽度
	Size tmpSize;

	//每个字的延迟时间
	float delay = 0.1f;
	//总时间
	float duration = 0.f;
	float scale = 1.f;

	//取得utf-8的字符串长度
	int utf8len = StringUtils::cc_utf8_strlen(text.c_str(), -1);
	if (utf8len == 0)
		return duration;
	//将字符串转化为utf-16
	unsigned short* pUniStr = new unsigned short[utf8len + 1];
	pUniStr[utf8len] = 0;

	const char* p = text.c_str();
	for (int i = 0;i < utf8len;i++)
	{
		pUniStr[i] = StringUtils::cc_utf8_get_char(p);
		p = cc_utf8_next_char(p);
	}
	std::u16string str(pUniStr);

	auto stringLen = str.length();
	//unsigned int stringLen = StringUtils::cc_wcslen(pUniStr);
	//统计行数
/*	for (unsigned int i = 0; i < stringLen - 1; i++)
	{
		unsigned short c = pUniStr[i];

		if (c == '\n')
		{
			quantityOfLines++;
		}
	}
	//由行高乘行数最得要显示的字符串占用的总高度  */
    totalHeight = m_pConfiguration->_commonHeight;
	//遍历所有的字
	for (unsigned int i = 0;i < stringLen;)
	{
		unsigned short c = str.at(i);
		//取得字相关精灵
		Sprite* fontChar = nullptr;
		int advance = 0;
		int xoffset = 0, yoffset = 0;
		//遇到换行符则进行换行处理
		if (c == '\r')
		{
			nextFontPositionX = 0;
			nextFontPositionY += m_pConfiguration->_commonHeight;
			totalHeight += m_pConfiguration->_commonHeight;
			i += 2;
			continue;
		}//控制信息
		else if (c == '\\')
		{
			int count = 0;
			fontChar = this->parseInfo(str, i, delay, scale, count);

			i += count;

			if (fontChar != nullptr)
			{
				auto size = fontChar->getContentSize();
				advance = size.width;
				xoffset = size.width;
				yoffset = size.height;
			}
			else 
				continue;
		}
		else
		{
			//查找当前节点的映射信息
			auto it = m_pConfiguration->_pBitmapFontMap->find(c);
			//获取当前字的映射信息
			auto& fontDef = it->second;
			Rect rect = Rect(fontDef.x, fontDef.y, fontDef.width, fontDef.height);
			//取得字相关精灵
			fontChar = this->popSpriteFromPool();
			auto texture = Director::getInstance()->getTextureCache()->addImage(m_pConfiguration->_atlasNames[fontDef.page]);
				
			fontChar->initWithTexture(texture, rect, false, rect.origin, rect.size);

			advance = fontDef.xadvance;
			xoffset = fontDef.xoffset + fontDef.width / 2.f;
			yoffset = fontDef.yoffset + fontDef.height / 2.f;

			i++;
		}
		fontChar->setVisible(!run);
		//保存
		TextStruct st(fontChar, delay);
		m_textStructs.push_back(st);
		//添加时间
		duration += delay;
		delay = 0.1f;
		//避免超过
		if (m_nWidth != 0 && nextFontPositionX + advance > m_nWidth)
		{
			nextFontPositionX = 0;
			nextFontPositionY += m_pConfiguration->_commonHeight;
			totalHeight += m_pConfiguration->_commonHeight;
		}
		//计算字的位置,注意：因为锚点设的精灵正中心，所以位置应该是左下角位置加上大小的一半再进行相关偏移和间距调整计算。
		fontChar->setPosition(nextFontPositionX + xoffset ,nextFontPositionY + yoffset);
		// 更新绘制下一个字的横向位置
		nextFontPositionX += advance;
		//设置色彩
        fontChar->setColorMod(m_color);
		//取得最长的一行的宽度  
		if (longestLine < nextFontPositionX) 
		{  
			longestLine = nextFontPositionX;
		}
	}
	//设置当前字符串在屏幕上占用的矩形位置  
    tmpSize.width  = (float) longestLine;  
    tmpSize.height = (float) totalHeight;  
    //调用基类CCNode的函数设置为原始大小  
    this->setContentSize(tmpSize);
    //释放字符串  
	delete[] pUniStr;

	return duration;
}

void Text::windRun(float dt)
{
	if (this->isWindOver())
		return ;

	auto& st = m_textStructs.at(m_nWindIndex);

	m_elapsed += dt;

	if (m_elapsed >= st.delay)
	{
		m_elapsed -= st.delay;
		m_nWindIndex++;
		st.sprite->setVisible(true);
	}
	return ;
}

bool Text::isWindOver() const
{
	return m_nWindIndex >= (int)m_textStructs.size();
}

void Text::windOver()
{
	while (m_nWindIndex < (int)m_textStructs.size())
	{
		auto& st = m_textStructs.at(m_nWindIndex++);

		st.sprite->setVisible(true);
	}
}

void Text::over()
{
	for (auto it = m_textStructs.begin(); it != m_textStructs.end();)
	{
		auto& st = *it;
		auto sprite = st.sprite;

		sprite->setVisible(false);
		m_spritePool.push_back(sprite);

		it = m_textStructs.erase(it);
	}
	m_nWindIndex = 0;
}

Font* Text::getFont(int fontSize)
{
	return FontCache::getInstance()->getFont(m_fontpath, fontSize);
}

Sprite* Text::popSpriteFromPool()
{
	Sprite* sprite = nullptr;

	if (m_spritePool.empty())
	{
		sprite = Sprite::create();

		this->addChild(sprite);
	}
	else
	{
		sprite = m_spritePool.front();
		sprite->setVisible(true);

		m_spritePool.erase(m_spritePool.begin());
	}
	return sprite;
}

Sprite* Text::parseInfo(const u16string& str, int from, float& delay, float& scale, int& count)
{
	unsigned int i = 0;
	auto c = str[from + 1];
	Sprite* sprite = nullptr;

	if (c == '.')
	{
		delay = 0.25f;
		count = 2;
	}
	else if (c == '|')
	{
		delay = 0.5f;
		count = 2;
	}
	else if (c == 'C')
	{
		int end = str.find(']',from + 1);
	}
	else if (c == 'I')
	{
		int end = str.find(']',from + 1);

		auto text = str.substr(from + 3).c_str();
		
		count = end - from + 1;

		//sprite = this->popSpriteFromPool();
		//sprite->setSpriteFrame(StaticData::getInstance()->getIconSpriteFrame(100));
	}

	return sprite;
}