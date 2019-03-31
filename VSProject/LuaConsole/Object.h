#ifndef __Object_H__
#define __Object_H__

//所有类的基类
class Object
{
protected:
	//引用计数器
	unsigned int m_uReference;
	//是否由内存管理器管理
	bool m_bManaged;
	unsigned int _uniqueID;
public:
	virtual bool init();
	Object();
	virtual ~Object();
	//保留
	void retain();
	//释放
	void release();
	//自动释放
	Object*autoRelease();
	//获得引用数量
	unsigned int getReferenceCount() const;
	//是否交给释放池
	bool beManaged(){return m_bManaged;}
	//是否相等
	virtual bool isEquals(const Object*obj);
	//友元
	friend class AutoreleasePool;
};
#endif