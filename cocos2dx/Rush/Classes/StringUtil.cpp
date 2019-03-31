#include "StringUtil.h"
#include<iostream>
StringUtil*StringUtil::m_pInstance = NULL;
StringUtil::StringUtil()
{
}
StringUtil::~StringUtil()
{
}
StringUtil*StringUtil::getInstance()
{
	if(m_pInstance == NULL)
		m_pInstance = new StringUtil();
	return m_pInstance;
}
ValueVector StringUtil::split(std::string srcStr,std::string sSep)
{
	ValueVector stringList;
	int size = srcStr.size();

	int startIndex = 0;
	int endIndex = 0;
	endIndex = srcStr.find(sSep);

	std::string lineStr;
	while(endIndex > 0)
	{
		lineStr = srcStr.substr(startIndex,endIndex);
		stringList.push_back(Value(lineStr));
		srcStr = srcStr.substr(endIndex+1,size);

		endIndex = srcStr.find(sSep);
	}
	if(srcStr.compare("") != 0)
		stringList.push_back(Value(srcStr));
	return stringList;
}
/*ValueVector StringUtil::split(std::string srcStr,std::string sSep)
{
	ValueVector stringList;
	std::vector<int> list;
	int i=0,j=0;
    int index = 0;

    int *next = new int[sSep.size()];
    getNext(sSep,next);

    while(srcStr[i]!='\0' && sSep[j]!='\0')
    {
        if(srcStr[i] == sSep[j])
        {
            i++;
            j++;
        }
        else
        {
            index += j - next[j];
            if(next[j] != -1)
                j = next[j];
            else
            {
                j = 0;
                ++i;
            }
        }
        if(sSep[j] == '\0')
        {
			list.push_back(index);
			
            index += j;
            j = 0;
        }
    }
	delete next;
	//·Ö¸î×Ö·û´®
	list.push_back(srcStr.size());
	for(int i=0,pre = -1;i<list.size();i++)
	{
		//log("%s",srcStr.substr(pre+1,list.at(i) - pre - 1).c_str());
		stringList.push_back(Value(srcStr.substr(pre+1,list.at(i) - pre-1)));
		pre = list.at(i);
	}
	return stringList;
}
void StringUtil::getNext(std::string sSep,int next[])
{
	next[0] = -1;
    int j=0,k = -1;
    while(j+1 < sSep.size())
    {
        if(k == -1 || sSep.at(k) == sSep.at(j))
        {
            ++k;
            ++j;
            if(sSep.at(k) != sSep.at(j))
                next[j] = k;
            else
                next[j] = next[k];
        }
        else
            k = next[k];
    }
}*/