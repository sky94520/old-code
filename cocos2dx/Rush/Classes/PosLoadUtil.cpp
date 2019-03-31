#include "PosLoadUtil.h"
#include "TowerPos.h"
PosLoadUtil*PosLoadUtil::m_pInstance = NULL;
PosLoadUtil::PosLoadUtil()
{
}
PosLoadUtil*PosLoadUtil::getInstance()
{
		if(m_pInstance == NULL)
			m_pInstance = new PosLoadUtil();
		return m_pInstance;
}
Vector<PosBase*> PosLoadUtil::loadPosWithFile(const char*sFilePath,PosType type,Node*container,int iLevel,bool isDebug)
{
	Vector<PosBase*> list;
	ValueMap fileDataMap = FileUtils::getInstance()->getValueMapFromFile(sFilePath);
	PosBase*pos = NULL;
	if(fileDataMap.empty())
		return list;
	int size = fileDataMap.size();
	for(int i = 1;i < size+1;i++)
	{
		Value value = fileDataMap.at(StringUtils::toString(i));
		ValueMap data = value.asValueMap();
		if(type == PosType::kMonsterPos)
			pos = MonsterPos::create(Point(data["x"].asInt(),data["y"].asInt()),isDebug);
		else
			pos = TowerPos::create(Point(data["x"].asInt(),data["y"].asInt()),isDebug);
		container->addChild(pos);
		list.pushBack(pos);
	}
	return list;
}