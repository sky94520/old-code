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
	Card *m_pSelectedCard;//��ǰѡ����
	vector<Card*> m_cards;//���Ӱ�
	Sprite*m_pSelectedHigh;//ѡ�и���
	vector<Sprite*> m_cardSlotBGList;//�����б�
public:
	CardLayer();
	~CardLayer();
	CREATE_FUNC(CardLayer);
	bool init();
	virtual void update(float dt);
	//������Ӱ�
	bool addCard(const std::string &name,CardType type);
	//�������Ӱ�
	void addCard(Card*card);
	//�Ƴ����Ӱ�
	void removeCard(Card*card);
	//�������Ӱ�
	Card*makeCard(const std::string& name,CardType type);
	//���ÿ��۸���
	void setCardSlotNum(unsigned int num,LevelCardType levelType);
	//����δʹ�ù��Ŀ���
	void hideUnusedCardSlot();
	//�����Ƿ���
	bool isFullOfCardSlot()const;
	//��ȡ��ǰ����Ŀ�Ƭ
	Card*getClickedCard(const Point&pos);
	//��ȡ��ǰѡ�еĿ�Ƭ
	Card*getSelectedCard();
	//���õ�ǰѡ�еĿ�Ƭ
	void setSelectedCard(Card*card);
	//���ѡ��
	void unselectedCard();
	void updateSelf();
private:
	Card*getItemForTouch(Touch*touch);
};
#endif