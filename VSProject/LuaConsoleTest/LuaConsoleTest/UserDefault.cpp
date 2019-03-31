#include "UserDefault.h"
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml_print.hpp"
#include "Value.h"

UserDefault*UserDefault::_pInstance = nullptr;
UserDefault::UserDefault()
{
}
UserDefault::~UserDefault()
{
}
UserDefault*UserDefault::getInstance()
{
	if(_pInstance == nullptr)
	{
		_pInstance = new UserDefault();
		_pInstance->init();
	}
	return _pInstance;
}
void UserDefault::purge()
{
	SDL_SAFE_DELETE(_pInstance);
}
bool UserDefault::init()
{
	_filePath = "save.xml";
	
	return true;
}
void UserDefault::setValueForKey(const std::string&key,const std::string&value)
{
	rapidxml::xml_document<> doc;
	//生命周期必须到解析完全
	rapidxml::file<>*file=nullptr;
	rapidxml::xml_node<>*root = nullptr;
	rapidxml::xml_node<>*node = nullptr;
	//添加文件头
	rapidxml::xml_node<>*head = doc.allocate_node(rapidxml::node_pi,
	doc.allocate_string("xml version='1.0' encoding='UTF-8'"));
	doc.append_node(head);
	try
	{
		file = new rapidxml::file<>(_filePath.c_str());
		doc.parse<0>(file->data());
		//获取root节点
		root = doc.first_node();
		//是否存在对应key
		node = root->first_node(key.c_str());
		//存在 删除后覆盖
		if(node)
		{
			root->remove_node(node);
			node = nullptr;
		}
		node = doc.allocate_node(rapidxml::node_element,key.c_str(),value.c_str());
		//覆盖该值
		root->append_node(node);
	}
	//不存在该文件 新建
	catch(std::runtime_error e)
	{
		//根节点
		root = doc.allocate_node(rapidxml::node_element,"root");
		doc.append_node(root);
		//分配该值
		node = doc.allocate_node(rapidxml::node_element,key.c_str(),value.c_str());
		//覆盖该值
		root->append_node(node);
	}
	std::string text;
	if(file)
		text += "<?xml version='1.0' encoding='UTF-8'?>\n";
	rapidxml::print(std::back_inserter(text),doc,0);
	std::ofstream fout;
	fout.open(_filePath,std::ios::out);
	fout.write(text.c_str(),text.size());
	fout.close();
	//std::cout<<text<<std::endl;
	SDL_SAFE_DELETE(file);
}
void UserDefault::setBoolForKey(const std::string&key,bool value)
{
	if(key.empty())
		return;
	std::string text = value == true?"true":"false";
	setValueForKey(key,text);
}
void UserDefault::setIntegerForKey(const std::string&key,int value)
{
	if(key.empty())
		return;
	setValueForKey(key,Value(value).asString());
}
void UserDefault::setFloatForKey(const std::string&key,float value)
{
	if(key.empty())
		return;
	setValueForKey(key,Value(value).asString());
}
void UserDefault::setDoubleForKey(const std::string&key,double value)
{
	if(key.empty())
		return;
	setValueForKey(key,Value(value).asString());
}
void UserDefault::setStringForKey(const std::string&key,const std::string&value)
{
	if(key.empty())
		return;
	setValueForKey(key,value);
}
std::string UserDefault::getValueForKey(const std::string&key)
{
	rapidxml::xml_document<> doc;
	try
	{
		rapidxml::file<> file(_filePath.c_str());
		doc.parse<0>(file.data());
		//root
		auto root = doc.first_node();
		//找到对应的node
		auto node = root->first_node(key.c_str());
		return node?node->value():"";
	}
	catch(std::runtime_error e)
	{
		return "";
	}
	return "";
}
bool UserDefault::getBoolForKey(const std::string&key,bool defaultValue)
{
	auto text = getValueForKey(key);
	if(text.empty())
		return defaultValue;
	if(text == "true")
		return true;
	else if(text == "false")
		return false;
}
int UserDefault::getIntegerForKey(const std::string&key,int defaultValue)
{
	auto text = getValueForKey(key);
	if(text.empty())
		return defaultValue;
	Value value = Value(text);
	return value.asInt();
}
float UserDefault::getFloatForKey(const std::string&key,float defaultValue)
{
	auto text = getValueForKey(key);
	if(text.empty())
		return defaultValue;
	Value value = Value(text);
	return value.asFloat();
}
double UserDefault::getDoubleForKey(const std::string&key,double defaultValue)
{
	auto text = getValueForKey(key);
	if(text.empty())
		return defaultValue;
	Value value = Value(text);
	return value.asDouble();
}
std::string UserDefault::getStringForKey(const std::string&key,const std::string&defaultValue)
{
	auto text = getValueForKey(key);
	if(text.empty())
		return defaultValue;
	return text;
}
bool UserDefault::isXMLExist()
{
	FILE*fp = fopen(_filePath.c_str(),"r");
	bool bRet = false;
	if(fp)
	{
		bRet = true;
		fclose(fp);
	}
	return fp;
}