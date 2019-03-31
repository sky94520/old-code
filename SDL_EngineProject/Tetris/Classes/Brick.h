#ifndef __Brick_H__
#define __Brick_H__
#include<vector>
#include "SDL_Engine/SDL_Engine.h"
#include "Command.h"

using namespace SDL;
using namespace std;
class RemoteControl;
/*��״*/
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

	virtual void transform();//����ת��
	virtual void decline();//�½�
	void left();//����
	void right();//����
	void undo();//����
	Shape&getShape();
	Size getTileSize();

	friend class TransformCommand;
};
#endif