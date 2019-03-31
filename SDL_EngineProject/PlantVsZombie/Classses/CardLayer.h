#ifndef __CardLayer_H__
#define __CardLayer_H__
#include<vector>
#include<algorithm>
#include "SDL_Engine/SDL_Engine.h"
#include "Card.h"

using namespace std;
using namespace SDL;
enum class LevelCardType;
class Card;

class CardLayer:public Node
{
private:
	Card *m_pSelectedCard;//当前选中项
	vector<Card*> m_cards;//种子包
	Sprite*m_pSelectedHigh;//选中高亮
	vector<Sprite*> m_cardSlotBGList;//卡槽列表
public:
	CardLayer();
	~CardLayer();
	CREATE_FUNC(CardLayer);
	bool init();
	virtual void update(float dt);
	//添加种子包
	bool addCard(const std::string &name,CardType type);
	//放入种子包
	void addCard(Card*card);
	//移除种子包
	void removeCard(Card*card);
	//制作种子包
	Card*makeCard(const std::string& name,CardType type);
	//设置卡槽个数
	void setCardSlotNum(unsigned int num,LevelCardType levelType);
	//隐藏未使用过的卡槽
	void hideUnusedCardSlot();
	//卡槽是否满
	bool isFullOfCardSlot()const;
	//获取当前点击的卡片
	Card*getClickedCard(const Point&pos);
	//获取当前选中的卡片
	Card*getSelectedCard();
	//设置当前选中的卡片
	void setSelectedCard(Card*card);
	//清除选中
	void unselectedCard();
	void updateSelf();
private:
	Card*getItemForTouch(Touch*touch);
};
#endif