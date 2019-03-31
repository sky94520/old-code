#include "QuestionLayer.h"
#include "DynamicData.h"
#include "Toast.h"

QuestionLayer::QuestionLayer()
	:m_pSelectedItem(nullptr),m_nTrueIndex(-1)
{
}
QuestionLayer::~QuestionLayer()
{
}
bool QuestionLayer::init()
{ 
	//��ӱ�������
	Node*csb = CSLoader::createNode("QuestionLayer.csb");
	this->addChild(csb);
	//�󶨰�ť�¼�
	auto okBtn = dynamic_cast<Widget*>(csb->getChildByName("ok_btn"));
	okBtn->addClickEventListener(CC_CALLBACK_1(QuestionLayer::okCallback,this));
	//���ؼ�
	auto backBtn = dynamic_cast<Widget*>(csb->getChildByName("back_btn"));
	backBtn->addClickEventListener(CC_CALLBACK_1(QuestionLayer::backCallback,this));
	//��ȡ����
	sqlite3*db = nullptr;
	char**result = nullptr;
	char*errorMsg;
	int row=0,column = 0;

	char* answers[4];
	//�����ݿ�
	sqlite3_open("fishing.db",&db);
	const char*sql = "select * from question order by RANDOM() limit 1";
	//ִ�����
	sqlite3_get_table(db,sql,&result,&row,&column,&errorMsg);
	auto id = result[column];
	auto question = result[column + 1];
	answers[0] = result[column + 2];
	answers[1] = result[column + 3];
	answers[2] = result[column + 4];
	answers[3] = result[column + 5];
	
	m_nTrueIndex = atoi(result[column + 6]) - 1;
	//��ȡ���
	auto questionScrollView = csb->getChildByName("question_scroll_view");
	auto questionText = dynamic_cast<Text*>(questionScrollView->getChildByName("question_text"));
	questionText->setString(question);

	//CheckBox
	//�������ѡ��
	bool bUsed[4] = {false,false,false,false};
	bool bChanged = false;

	Node*answerPanel = csb->getChildByName("answer_panel");
	for(int i=0;i<4;i++)
	{
		auto name = StringUtils::format("answer_layout%d",i+1);
		auto layout = answerPanel->getChildByName(name);
		auto answerText = dynamic_cast<Text*>(layout->getChildByName("answer_text"));
		//answerText->setString(answers[i]);
		while(1)
		{
			int n = rand()%4;
			//���ѡ��û�б�ʹ�ù�
			if(bUsed[n] == false)
			{
				//����ȷ����ȷ��
				if(bChanged == false && n == m_nTrueIndex)
				{
					bChanged = true;
					m_nTrueIndex = i;
				}
				bUsed[n]=true;
				answerText->setString(answers[n]);
				break;
			}
		}

		m_pAnswers[i] = dynamic_cast<CheckBox*>(layout->getChildByName("answer_checkbox"));
		m_pAnswers[i]->addClickEventListener(CC_CALLBACK_1(QuestionLayer::onBtnClick,this));
		//Ĭ�϶�û��ѡ��
		m_pAnswers[i]->setSelected(false);
	}
	//�ͷ�
	sqlite3_free_table(result);
	sqlite3_free(errorMsg);
	sqlite3_close(db);
	return true;
}
void QuestionLayer::onBtnClick(Ref*sender)
{
	auto selectedItem = dynamic_cast<CheckBox*>(sender);
	//��ǰû��ѡ����
	if(m_pSelectedItem == nullptr)
	{
		m_pSelectedItem = selectedItem;
	}
	else
	{
		//�л�ѡ����
		if(m_pSelectedItem != selectedItem)
		{
			m_pSelectedItem->setSelected(false);
			m_pSelectedItem = selectedItem;
		}
		else//��ͬ���л�
		{
			m_pSelectedItem->setSelected(true);
		}
	}
}
void QuestionLayer::okCallback(Ref*sender)
{
	auto valueMap = FileUtils::getInstance()->getValueMapFromFile("strings.xml");
	//���û��ѡ�������ʾ
	if(m_pSelectedItem == nullptr)
	{
		Toast::makeText(this,valueMap.at("str1").asString(),3.f);
	}
	else
	{
		//���ٻش����
		int questionTimes = DynamicData::getInstance()->getAnswerTimes();
		DynamicData::getInstance()->setAnswerTimes(questionTimes - 1);
		
		Node*parent = this->getParent();

		//ѡ������ȷ��
		if(m_pSelectedItem == m_pAnswers[m_nTrueIndex])
		{
			//���ӳ��ֻ���
			DynamicData::getInstance()->addAtkTimes(+5);
			Toast::makeText(parent,valueMap.at("str2").asString(),3.f);
			//
			this->removeFromParent();
		}
		else
		{
			//�۳����ֻ���
			DynamicData::getInstance()->reduceAtkTimes();

			Toast::makeText(parent,valueMap.at("str3").asString(),3.f);
			this->removeFromParent();
		}
	}
}
void QuestionLayer::backCallback(Ref*sender)
{
	this->removeFromParent();
}