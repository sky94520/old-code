#include "Object.h"

Object::Object():_uniqueID(0)
{
	//定义一个静态变量作为实例对象引用器，每个对象唯一，只会多，不会少
	static unsigned int uObjectCount=0;
	uObjectCount++;
	//当类进行实例化时，设置为1
	m_uReference=1;
	m_bManaged=false;
	//log("构造函数\n");
	_uniqueID = uObjectCount;
}
bool Object::init()
{
	return true;
}
Object::~Object()
{
	//被自动释放管理器管理，调用内存管理器
	if(m_bManaged)
	{
		//PoolManager::getInstance()->removeObject(this);
	}
	//log("析构函数\n");
}
void Object::retain()
{
	++m_uReference;
}
void Object::release()
{
	--m_uReference;
	//如果引用计数为0 释放
	if(m_uReference==0)
		delete this;
}
//不重复插入
Object*Object::autoRelease()
{
	if(m_bManaged==false)
	{
		//加入自动释放池中
		//ThePoolManager::getInstance()->addObject(this);
		m_bManaged=true;
	}
	return this;
}
unsigned int Object::getReferenceCount() const
{
	return m_uReference;
}
bool Object::isEquals(const Object*obj)
{
	return this==obj;
}