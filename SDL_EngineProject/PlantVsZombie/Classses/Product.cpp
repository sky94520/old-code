#include "Product.h"

Product::Product()
	:m_productType(ProductType::None),m_nNumber(0)
	,m_bClicked(false),m_bUpdate(false)
	,m_bDead(false),m_duration(0.f)
{
}

Product::~Product()
{
}

bool Product::init()
{
	return true;
}

void Product::update(float dt)
{
	//如果死亡或者已经点击过了,则不进行更新
	if (m_bDead || m_bClicked)
		return;
	if (m_bUpdate)
	{
		m_duration -= dt;
		if (m_duration <= 0.f)
			m_bDead = true;
	}
}