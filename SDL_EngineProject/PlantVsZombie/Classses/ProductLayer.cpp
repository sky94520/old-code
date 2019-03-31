#include "ProductLayer.h"
#include "Product.h"
#include "StaticData.h"
#include "Entity.h"

ProductLayer::ProductLayer()
{
}

ProductLayer::~ProductLayer()
{
}

bool ProductLayer::init()
{
	return true;
}

void ProductLayer::update(float dt)
{
	for (auto it = m_products.begin();it != m_products.end();)
	{
		auto product = *it;
		//��ǰ�����������ٽ��и���
		if (product->isDead())
		{
			product->removeFromParent();
			it = m_products.erase(it);
		}
		else
		{
			if (product->isUpdate())
				product->update(dt);
			it++;
		}
	}
}

void ProductLayer::makeSun(int number,FiniteTimeAction*action,const Point&bornPos,Layer*layer)
{
	//����̫��
	Product*sun = Product::create();
	//���ø�������
	sun->setNumber(number);
	sun->setClicked(false);
	sun->setUpdate(false);
	sun->setDead(false);
	sun->setDuration(10.f);
	sun->setProductType(ProductType::Sun);
	sun->setPosition(bornPos);

	layer->addChild(sun);
	m_products.push_back(sun);
	//���ö���
	auto animationName = "Sun";
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	//��ȡ��һ֡
	auto firstFrame = (animation->getFrames().at(0))->getSpriteFrame();
	//������ͼ
	sun->bindSpriteWithSpriteFrame(firstFrame);
	//����number����̫����С
	if (number < 25)
		sun->getSprite()->setScale(0.5f,0.5f);

	//���ж����Ͷ���
	sun->getSprite()->runAction(Animate::create(animation));

	CallFunc*end = CallFunc::create([sun]()
	{
		sun->setUpdate(true);
	});

	auto seq = Sequence::createWithTwoActions(action,end);
	sun->runAction(seq);
}

Product*ProductLayer::getClickedProduct(const Point&pos)
{
	for (auto product : m_products)
	{
		auto rect = product->getBoundingBox();

		if (rect.containsPoint(pos) && !product->isClicked())
			return product;
	}

	return nullptr;
}