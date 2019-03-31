#ifndef __Object_H__
#define __Object_H__

//������Ļ���
class Object
{
protected:
	//���ü�����
	unsigned int m_uReference;
	//�Ƿ����ڴ����������
	bool m_bManaged;
	unsigned int _uniqueID;
public:
	virtual bool init();
	Object();
	virtual ~Object();
	//����
	void retain();
	//�ͷ�
	void release();
	//�Զ��ͷ�
	Object*autoRelease();
	//�����������
	unsigned int getReferenceCount() const;
	//�Ƿ񽻸��ͷų�
	bool beManaged(){return m_bManaged;}
	//�Ƿ����
	virtual bool isEquals(const Object*obj);
	//��Ԫ
	friend class AutoreleasePool;
};
#endif