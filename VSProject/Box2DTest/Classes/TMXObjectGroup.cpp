#include "TMXObjectGroup.h"
TMXObject::TMXObject(rapidxml::xml_node<>*root)
{
	TMXObject();

	id = root->first_attribute("id")->value();
	x = atof(root->first_attribute("x")->value());
	y = atof(root->first_attribute("y")->value());
	width = atof(root->first_attribute("width")->value());
	height = atof(root->first_attribute("height")->value());
	//可能存在的属性
	if(root->first_attribute("name"))
		name = root->first_attribute("name")->value();
	if(root->first_attribute("type"))
		type = root->first_attribute("type")->value();
	//properties
	for(auto node = root->first_node("properties")->first_node();node;node = node->next_sibling())
	{
		std::string key = node->first_attribute("name")->value();
		std::string value = node->first_attribute("value")->value();

		properties.insert(std::make_pair(key,value));
	}
}
std::map<std::string,std::string> TMXObject::getProperties()const
{
	return properties;
}
//-----------------------TMXObjectGroup-----------------------------
TMXObjectGroup::TMXObjectGroup()
	:_groupName("")
{
}
TMXObjectGroup::~TMXObjectGroup()
{
	for(auto iter = _objects.begin();iter != _objects.end();)
	{
		auto object = *iter;
		iter = _objects.erase(iter);
		delete object;
	}
}
TMXObjectGroup*TMXObjectGroup::create(rapidxml::xml_node<>*root)
{
	auto objectGroup = new TMXObjectGroup();
	if(objectGroup && objectGroup->init(root))
		objectGroup->autoRelease();
	else
		SDL_SAFE_DELETE(objectGroup);
	return objectGroup;
}
bool TMXObjectGroup::init(rapidxml::xml_node<>*root)
{
	_groupName = root->first_attribute("name")->value();
	for(auto node = root->first_node();node;node = node->next_sibling())
	{
		std::string name = node->name();
		if(name == "object")
			parseObject(node);
	}
	return true;
}
TMXObject*TMXObjectGroup::getObject(const std::string&objectName)
{
	auto iter = std::find_if(_objects.begin(),_objects.end(),[objectName](TMXObject*object)
	{
		return object->name == objectName;
	});
	if(iter != _objects.end())
		return *iter;
	return nullptr;
}
std::string TMXObjectGroup::getGroupName()const
{
	return _groupName;
}
void TMXObjectGroup::setGroupName(const std::string&groupName)
{
	_groupName = groupName;
}
void TMXObjectGroup::parseObject(rapidxml::xml_node<>*root)
{
	TMXObject*object = new TMXObject(root);
	_objects.push_back(object);
}