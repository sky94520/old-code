#ifndef __ColumnLayer_H__
#define __ColumnLayer_H__
#include<vector>
#include "SDL_Engine/SDL_Engine.h"
using namespace std;
using namespace SDL;
class DoubleColumn;

class ColumnLayer:public Layer
{
	SDL_SYNTHESIZE(float,m_speed,Speed);
private:
	vector<DoubleColumn*> m_columns;
public:
	ColumnLayer();
	~ColumnLayer();
	CREATE_FUNC(ColumnLayer);
	bool init();

	virtual void update(float dt);

	vector<DoubleColumn*>& getColumns();
};
#endif