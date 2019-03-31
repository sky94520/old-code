#ifndef __Text_H__
#define __Text_H__
#include <map>
#include <vector>
#include <string>
#include <cstdlib>
#include "SDL_Engine/SDL_Engine.h"

using namespace std;
USING_NS_SDL;

struct TextStruct
{
public:
	Sprite* sprite;
	float delay;
public:
	TextStruct(Sprite* sprite, float delay)
		:sprite(sprite)
		,delay(delay)
	{
	}
};

class Text : public Node
{
private:
	BMFontConfiguration* m_pConfiguration;
	int m_nWidth;
	vector<TextStruct> m_textStructs;
	//�����
	vector<Sprite*> m_spritePool;
	//��ǰ������ߴ�
	int m_fontSize;
	//��ǰ��ɫ
	Color3B m_color;
	//����·��
	string m_fontpath;
	//��ǰ��ʾ���ľ�������
	int m_nWindIndex;
	//���ŵ�ʱ�䣬�͡���Ҫ���ڶ�ʱ��ʾ�ַ�
	float m_elapsed;
public:
	Text();
	~Text();
	static Text* create(const string& fontFile, int width, const Color3B& color);

	bool init(const string& fontFile, int width, const Color3B& color);
	
	float wind(const string& text, const Size& size, const Color4B& color, bool run);
	//����Ч��
	void windRun(float dt);
	//�����Ƿ����
	bool isWindOver() const;
	void windOver();
	//����
	void over();
private:
	Font* getFont(int fontSize);
	Sprite* popSpriteFromPool();
	Sprite* parseInfo(const u16string& str, int from, float& delay, float& scale, int& count);
};
#endif