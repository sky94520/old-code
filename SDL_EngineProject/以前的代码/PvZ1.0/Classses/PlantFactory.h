#ifndef __PlantFactory_H__
#define __PlantFactory_H__
#include<unordered_map>
#include<string>
#include "BaseCreator.h"
#include "SDL_Engine/SDL_Engine.h"
using namespace std;
using namespace SDL;
class Plant;
class PlantFactory:public Object
{
private:
	unordered_map<string,BaseCreator*> m_creators;
	static PlantFactory*m_pInstance;
private:
	PlantFactory();
	~PlantFactory();
public:
	static PlantFactory*getInstance()
	{
		if(m_pInstance == nullptr)
			m_pInstance = new PlantFactory();
		return m_pInstance;
	}
	void purge();
	bool registerType(const std::string& type,BaseCreator*pCreator);
	Plant*create(const std::string&type)const; 
};
#endif