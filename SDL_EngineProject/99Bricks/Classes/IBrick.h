#ifndef __IBrick_H__
#define __IBrick_H__
/*����ӿڣ�������һϵ�е�����*/
class IBrick
{
public:
	virtual void setFriction(float friction)=0;//������Ħ����
	virtual void setRestitution(float restitution)=0;//���õ���
	virtual void setVelocity(float velocityX,float velocityY)=0;//�������ٶ�
	virtual void setBrickScale(float x,float y)=0;//��������
	virtual void setBodyType(unsigned int type)=0;//��������
	virtual void setFixedRotation(bool fixed)=0;//�Ƿ��ֹ������ת
};
#endif