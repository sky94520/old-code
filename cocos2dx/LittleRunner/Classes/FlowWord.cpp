#include "FlowWord.h"

bool FlowWord::init() 
{
	m_textLab = Label::create("", "Arial", 35);
	m_textLab->setColor(Color3B(255, 0, 0));
	m_textLab->setAnchorPoint(Point(1, 0));
	m_textLab->setVisible(false);

	this->addChild(m_textLab);
	return true;
}

void FlowWord::showWord( const char* text, Point pos ) 
{
	m_textLab->setString(text);
	m_textLab->setPosition(pos);
	m_textLab->setVisible(true);

	/* ��������������Ŵ����С */
    auto scaleLarge = ScaleTo::create(0.3f, 2.5f, 2.5f);
    auto scaleSmall = ScaleTo::create(0.5f, 0.5f, 0.5f);

	UserDefault
    auto callFunc = CallFunc::create([&](){
		auto t = m_textLab;
        /* �����������Ӹ��ڵ���ɾ������ */
        m_textLab->setVisible(false);
        m_textLab->removeFromParentAndCleanup(true);
		log("%d",m_textLab->getReferenceCount());
    });

    auto actions = Sequence::create(scaleLarge, scaleSmall, callFunc, NULL);

	m_textLab->runAction(actions);
}


