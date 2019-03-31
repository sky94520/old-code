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
	//添加背景布局
	Node*csb = CSLoader::createNode("QuestionLayer.csb");
	this->addChild(csb);
	//绑定按钮事件
	auto okBtn = dynamic_cast<Widget*>(csb->getChildByName("ok_btn"));
	okBtn->addClickEventListener(CC_CALLBACK_1(QuestionLayer::okCallback,this));
	//返回键
	auto backBtn = dynamic_cast<Widget*>(csb->getChildByName("back_btn"));
	backBtn->addClickEventListener(CC_CALLBACK_1(QuestionLayer::backCallback,this));
	//读取数据
	sqlite3*db = nullptr;
	char**result = nullptr;
	char*errorMsg;
	int row=0,column = 0;

	char* answers[4];
	//打开数据库
	sqlite3_open("fishing.db",&db);
	const char*sql = "select * from question order by RANDOM() limit 1";
	//执行语句
	sqlite3_get_table(db,sql,&result,&row,&column,&errorMsg);
	auto id = result[column];
	auto question = result[column + 1];
	answers[0] = result[column + 2];
	answers[1] = result[column + 3];
	answers[2] = result[column + 4];
	answers[3] = result[column + 5];
	
	m_nTrueIndex = atoi(result[column + 6]) - 1;
	//获取题干
	auto questionScrollView = csb->getChildByName("question_scroll_view");
	auto questionText = dynamic_cast<Text*>(questionScrollView->getChildByName("question_text"));
	questionText->setString(question);

	//CheckBox
	//随机打乱选项
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
			//这个选项没有被使用过
			if(bUsed[n] == false)
			{
				//重新确定正确项
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
		//默认都没有选中
		m_pAnswers[i]->setSelected(false);
	}
	//释放
	sqlite3_free_table(result);
	sqlite3_free(errorMsg);
	sqlite3_close(db);
	return true;
}
void QuestionLayer::onBtnClick(Ref*sender)
{
	auto selectedItem = dynamic_cast<CheckBox*>(sender);
	//当前没有选中项
	if(m_pSelectedItem == nullptr)
	{
		m_pSelectedItem = selectedItem;
	}
	else
	{
		//切换选中项
		if(m_pSelectedItem != selectedItem)
		{
			m_pSelectedItem->setSelected(false);
			m_pSelectedItem = selectedItem;
		}
		else//相同则不切换
		{
			m_pSelectedItem->setSelected(true);
		}
	}
}
void QuestionLayer::okCallback(Ref*sender)
{
	auto valueMap = FileUtils::getInstance()->getValueMapFromFile("strings.xml");
	//如果没有选中项，则提示
	if(m_pSelectedItem == nullptr)
	{
		Toast::makeText(this,valueMap.at("str1").asString(),3.f);
	}
	else
	{
		//减少回答次数
		int questionTimes = DynamicData::getInstance()->getAnswerTimes();
		DynamicData::getInstance()->setAnswerTimes(questionTimes - 1);
		
		Node*parent = this->getParent();

		//选择了正确答案
		if(m_pSelectedItem == m_pAnswers[m_nTrueIndex])
		{
			//增加出手机会
			DynamicData::getInstance()->addAtkTimes(+5);
			Toast::makeText(parent,valueMap.at("str2").asString(),3.f);
			//
			this->removeFromParent();
		}
		else
		{
			//扣除出手机会
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