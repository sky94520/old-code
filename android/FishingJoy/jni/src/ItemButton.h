#ifndef __ItemButton_H__
#define __ItemButton_H__

#include<string>
#include "SDL_Engine/SDL_Engine.h"

using namespace std;
using namespace SDL;

class NumberSprite;
/*��ť����*/
enum class ButtonType
{
	None,
	SuperWeapon,//��������
	HalfEnergy,//һ�������ֵ
	Bullet,//�ӵ�
};
class ItemButton:public MenuItem
{
private:
	Sprite*m_pNormalSprite;
	Sprite*m_pDisabelSprite;
	NumberSprite*m_pNumberSprite;
	ButtonType m_buttonType;
public:
	ItemButton();
	~ItemButton();
	CREATE_FUNC(ItemButton);
	static ItemButton*create(Sprite*normalSprite,unsigned int number,ButtonType type);

	bool init();
	bool init(Sprite*normalSprite,unsigned int number,ButtonType type);
	//����������ť
	void setNormalSprite(Sprite*normalSprite);
	Sprite*getNormalSprite()const;
	//������
	void setNumber(unsigned int number);
	unsigned int getNumber()const;

	void setButtonType(ButtonType type);
	ButtonType getButtonType()const;
public://override
	virtual void setEnabled(bool enable);
	//override
	virtual void selected();
	virtual void unselected();
private:
	void updateImagesVisibility();
};
#endif