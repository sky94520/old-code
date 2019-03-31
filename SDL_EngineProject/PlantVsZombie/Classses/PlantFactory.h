#ifndef __PlantFactory_H__
#define __PlantFactory_H__
#include<string>
#include "SDL_Engine/SDL_Engine.h"
using namespace std;
using namespace SDL;

class Plant;
class Pea;
class WallNut;
class Catapult;
class NightPlant;

class PlantFactory : public Object
{
public:
	PlantFactory();
	~PlantFactory();
	CREATE_FUNC(PlantFactory);
	bool init();

	Plant*makePlant(const string& plantName);
private:
	Pea*makePea(const string& plantName);
	WallNut*makeNut(const string& plantName);
	Catapult*makeCatapult(const string&name);
	NightPlant*makeNightPlant(const string& name);
};
#endif