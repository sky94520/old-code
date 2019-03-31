#ifndef __IBrick_H__
#define __IBrick_H__
/*方块接口，定义了一系列的内容*/
class IBrick
{
public:
	virtual void setFriction(float friction)=0;//可设置摩擦力
	virtual void setRestitution(float restitution)=0;//设置弹性
	virtual void setVelocity(float velocityX,float velocityY)=0;//设置线速度
	virtual void setBrickScale(float x,float y)=0;//设置缩放
	virtual void setBodyType(unsigned int type)=0;//设置类型
	virtual void setFixedRotation(bool fixed)=0;//是否禁止刚体旋转
};
#endif