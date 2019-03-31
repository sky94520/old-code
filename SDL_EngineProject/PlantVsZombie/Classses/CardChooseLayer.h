#ifndef __CardChooseLayer_H__
#define __CardChooseLayer_H__
#include <string>
#include <vector>
#include <functional>
#include "SDL_Engine/SDL_Engine.h"

enum class CardType;

class Card;

using namespace std;
using namespace SDL;

enum class LevelCardType;

class CardChooseLayerDelegate
{
public:
	virtual ~CardChooseLayerDelegate(){}
	virtual Card*makeCard(const std::string& name,CardType type) = 0;
	virtual void clickCardChooseStartBtn() = 0;
	virtual LevelCardType getLevelCardShowType()const = 0;
};
class CardChooseLayer : public Layer
{
private:
	Sprite*m_pSpriteBG;
	ui::Button* m_pStartGameBtn;
	CardChooseLayerDelegate*m_pDelegate;
	vector<Card*> m_cards;
public:
	CardChooseLayer();
	~CardChooseLayer();
	CREATE_FUNC(CardChooseLayer);
	bool init();

	void setDelegate(CardChooseLayerDelegate*pDelegate);
	//��ʼ����Ƭ
	//void initlizeCard();
	void show(const vector<string>& cardNameList);
	void hide();
	//��ȡ��ǰ����Ŀ�Ƭ
	Card*getClickedCard(const Point&pos);
	//���뿨Ƭ
	bool addCard(Card*card);
	//�Ƴ���Ӧ�Ŀ�Ƭ
	bool removeCard(Card*card);
	//���õ�ǰ��ť�Ƿ����
	void setStartBtnEnable(bool enable);
private:
	void start(Object*sender);
};
#endif