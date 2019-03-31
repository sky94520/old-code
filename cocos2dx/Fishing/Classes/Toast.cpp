#include "Toast.h"
namespace Toast
{
	void makeText(Node*node,const std::string&text,float delay)
	{
		//创建一个Label
		Label*label = Label::create(text,"fonts/DroidSansFallback.ttf",15);
		Size s = label->getContentSize();
		label->setPosition(s.width/2,s.height/2);
		//创建一个能包裹主label的LayerColor
		LayerColor*layerColor = LayerColor::create(Color4B(0,0,0,128),s.width,s.height);
		layerColor->addChild(label);
		//创建动画
		FadeTo*fadeTo = FadeTo::create(0.2f,128);
		FadeOut*fadeOut = FadeOut::create(0.2f);
		DelayTime*delayTime = DelayTime::create(delay);
		RemoveSelf*removeSelf = RemoveSelf::create(true);
		//运行动画
		layerColor->runAction(Sequence::create(fadeTo,delayTime,fadeOut,removeSelf,nullptr));
		//设置位置
		Size visibleSize = Director::getInstance()->getVisibleSize();
		layerColor->setPosition(visibleSize.width/2 - s.width/2,visibleSize.height/2);
		//添加到node结点
		node->addChild(layerColor);
	}
}