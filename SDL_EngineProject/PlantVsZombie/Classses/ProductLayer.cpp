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
		//当前已死亡，则不再进行更新
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
	//生成太阳
	Product*sun = Product::create();
	//设置各种属性
	sun->setNumber(number);
	sun->setClicked(false);
	sun->setUpdate(false);
	sun->setDead(false);
	sun->setDuration(10.f);
	sun->setProductType(ProductType::Sun);
	sun->setPosition(bornPos);

	layer->addChild(sun);
	m_products.push_back(sun);
	//设置动画
	auto animationName = "Sun";
	auto animation = AnimationCache::getInstance()->getAnimation(animationName);
	//获取第一帧
	auto firstFrame = (animation->getFrames().at(0))->getSpriteFrame();
	//设置贴图
	sun->bindSpriteWithSpriteFrame(firstFrame);
	//根据number设置太阳大小
	if (number < 25)
		sun->getSprite()->setScale(0.5f,0.5f);

	//运行动画和动作
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