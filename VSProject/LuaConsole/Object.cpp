#include "Object.h"

Object::Object():_uniqueID(0)
{
	//����һ����̬������Ϊʵ��������������ÿ������Ψһ��ֻ��࣬������
	static unsigned int uObjectCount=0;
	uObjectCount++;
	//�������ʵ����ʱ������Ϊ1
	m_uReference=1;
	m_bManaged=false;
	//log("���캯��\n");
	_uniqueID = uObjectCount;
}
bool Object::init()
{
	return true;
}
Object::~Object()
{
	//���Զ��ͷŹ��������������ڴ������
	if(m_bManaged)
	{
		//PoolManager::getInstance()->removeObject(this);
	}
	//log("��������\n");
}
void Object::retain()
{
	++m_uReference;
}
void Object::release()
{
	--m_uReference;
	//������ü���Ϊ0 �ͷ�
	if(m_uReference==0)
		delete this;
}
//���ظ�����
Object*Object::autoRelease()
{
	if(m_bManaged==false)
	{
		//�����Զ��ͷų���
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