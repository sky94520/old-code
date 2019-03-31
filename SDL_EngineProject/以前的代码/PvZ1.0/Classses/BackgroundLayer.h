#ifndef __BackgroundLayer_H__
#define __BackgroundLayer_H__
#include "SDL_Engine/SDL_Engine.h"
using namespace SDL;
class Carrier;
class BackgroundLayer:public Layer
{
	SDL_SYNTHESIZE(float,m_elapsed,Elapsed);//����ֵ
	SDL_SYNTHESIZE(float,m_skillCD,SkillCD);//����̫���ļ��
	SDL_SYNTHESIZE(std::string,m_zombiePath,ZombiePath);//��ʬ�����ļ�
private:
	Point m_startPos;//(256,80)Ϊ��ʼֵ
	Size m_size;//ÿ������Ĵ�С
	Carrier*m_pCarriers[5][9];//ֲ������
	Sprite*m_pBG;//����
	bool m_bDay;//�Ƿ��ǰ���
public:
	BackgroundLayer();
	~BackgroundLayer();
	CREATE_FUNC(BackgroundLayer);
	bool init();

	virtual void update(float dt);
	//���س���
	void loadLevel(const std::string&level);
	//��ʼ�������ͷ�ʱ��
	void initSkillCD();
	//ͨ������ֵ��ȡָ��������
	Carrier*getCarrierByPos(const Point&pos);
	Rect getLegalRect()const;
	//�Ƿ��ǰ���
	bool isDay()const;

};
#endif