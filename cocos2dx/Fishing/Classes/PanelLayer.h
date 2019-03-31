#ifndef __PanelLayer_H__
#define __PanelLayer_H__
#include<map>
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class NeedfulFishCompent;

class PanelLayerDelegate
{
public:
	virtual ~PanelLayerDelegate(){}
	virtual void gamePause()=0;
	virtual void showQuestionLayer()=0;
};
/*���㣬ֻ����ʾ��ǰʣ�������
��Ҫ��׽���������������*/
/*���¹���:����׽��һ����ʱ�������Ҫ���㣬����ʾ�����㻹ʣ�¼�������*/
class PanelLayer:public Layer
{
private:
	Label*m_pTimesLabel;//ʣ�ಽ��
	PanelLayerDelegate*m_pDelegate;
	map<int,NeedfulFishCompent*> m_compents;
	bool m_bShowAllComp;//�Ƿ��Ѿ���ʾ�����е����
public:
	PanelLayer();
	~PanelLayer();
	CREATE_FUNC(PanelLayer);
	bool init();
	void clean();

	void setDelegate(PanelLayerDelegate*pDelegate);
	//��ʾ���ؿ�����Ҫ��ȫ������
	void showAllNeedfulFishesComp();
	//����
	void hideAllNeedfulFishesComp();
	//�Ƿ��������
	bool isClickedComponents(const Point&pos)const;
	bool isShowAllComp()const;
	void setShowAllComp(bool c);

	bool initWithTimes();
	bool initWithNeedfulFishes();
private:
	void updateSelf(Ref*sender);
	//��Ϸ��ͣ��ť�ص�����
	void gamePause(Ref*obj);
	//��ʾ�������
	void showQuestionLayer(Ref*sender);
};
#endif