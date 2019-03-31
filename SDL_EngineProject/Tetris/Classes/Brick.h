#ifndef __Brick_H__
#define __Brick_H__
#include<vector>
#include "SDL_Engine/SDL_Engine.h"
#include "Command.h"

using namespace SDL;
using namespace std;
class RemoteControl;
/*ÐÎ×´*/
typedef struct
{
	Point p[4];
}Shape;
class Brick:public Node
{
	SDL_SYNTHESIZE(string,m_spriteName,SpriteName);
protected:
	vector<Shape> m_shapes;
	int m_nCurIndex;
	RemoteControl*m_pControl;
public:
	Brick();
	~Brick();
	static Brick*create(const vector<Shape>&shapes,const string&spriteName);
	bool init(const vector<Shape>&shapes,const string&spriteName);

	virtual void transform();//·½¿é×ª»»
	virtual void decline();//ÏÂ½µ
	void left();//ÓÒÒÆ
	void right();//×óÒÆ
	void undo();//³·Ïú
	Shape&getShape();
	Size getTileSize();

	friend class TransformCommand;
};
#endif