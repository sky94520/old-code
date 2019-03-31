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

	int nextFontPositionX = 0;  //��һ���ֵĺ������λ��  
	int nextFontPositionY = 0;   //��һ���ֵ��������λ�� 
	unsigned int quantityOfLines = 1;
	unsigned int totalHeight = 0;//�ַ������ܸ߶�
	int longestLine = 0;        // ���һ�еĿ��
	Size tmpSize;

	//ÿ���ֵ��ӳ�ʱ��
	float delay = 0.1f;
	//��ʱ��
	float duration = 0.f;
	float scale = 1.f;

	//ȡ��utf-8���ַ�������
	int utf8len = StringUtils::cc_utf8_strlen(text.c_str(), -1);
	if (utf8len == 0)
		return duration;
	//���ַ���ת��Ϊutf-16
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
	//ͳ������
/*	for (unsigned int i = 0; i < stringLen - 1; i++)
	{
		unsigned short c = pUniStr[i];

		if (c == '\n')
		{
			quantityOfLines++;
		}
	}
	//���и߳��������Ҫ��ʾ���ַ���ռ�õ��ܸ߶�  */
    totalHeight = m_pConfiguration->_commonHeight;
	//�������е���
	for (unsigned int i = 0;i < stringLen;)
	{
		unsigned short c = str.at(i);
		//ȡ������ؾ���
		Sprite* fontChar = nullptr;
		int advance = 0;
		int xoffset = 0, yoffset = 0;
		//�������з�����л��д���
		if (c == '\r')
		{
			nextFontPositionX = 0;
			nextFontPositionY += m_pConfiguration->_commonHeight;
			totalHeight += m_pConfiguration->_commonHeight;
			i += 2;
			continue;
		}//������Ϣ
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
			//���ҵ�ǰ�ڵ��ӳ����Ϣ
			auto it = m_pConfiguration->_pBitmapFontMap->find(c);
			//��ȡ��ǰ�ֵ�ӳ����Ϣ
			auto& fontDef = it->second;
			Rect rect = Rect(fontDef.x, fontDef.y, fontDef.width, fontDef.height);
			//ȡ������ؾ���
			fontChar = this->popSpriteFromPool();
			auto texture = Director::getInstance()->getTextureCache()->addImage(m_pConfiguration->_atlasNames[fontDef.page]);
				
			fontChar->initWithTexture(texture, rect, false, rect.origin, rect.size);

			advance = fontDef.xadvance;
			xoffset = fontDef.xoffset + fontDef.width / 2.f;
			yoffset = fontDef.yoffset + fontDef.height / 2.f;

			i++;
		}
		fontChar->setVisible(!run);
		//����
		TextStruct st(fontChar, delay);
		m_textStructs.push_back(st);
		//���ʱ��
		duration += delay;
		delay = 0.1f;
		//���ⳬ��
		if (m_nWidth != 0 && nextFontPositionX + advance > m_nWidth)
		{
			nextFontPositionX = 0;
			nextFontPositionY += m_pConfiguration->_commonHeight;
			totalHeight += m_pConfiguration->_commonHeight;
		}
		//�����ֵ�λ��,ע�⣺��Ϊê����ľ��������ģ�����λ��Ӧ�������½�λ�ü��ϴ�С��һ���ٽ������ƫ�ƺͼ��������㡣
		fontChar->setPosition(nextFontPositionX + xoffset ,nextFontPositionY + yoffset);
		// ���»�����һ���ֵĺ���λ��
		nextFontPositionX += advance;
		//����ɫ��
        fontChar->setColorMod(m_color);
		//ȡ�����һ�еĿ��  
		if (longestLine < nextFontPositionX) 
		{  
			longestLine = nextFontPositionX;
		}
	}
	//���õ�ǰ�ַ�������Ļ��ռ�õľ���λ��  
    tmpSize.width  = (float) longestLine;  
    tmpSize.height = (float) totalHeight;  
    //���û���CCNode�ĺ�������Ϊԭʼ��С  
    this->setContentSize(tmpSize);
    //�ͷ��ַ���  
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