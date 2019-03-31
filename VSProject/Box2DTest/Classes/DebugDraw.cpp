#include "DebugDraw.h"
DebugDraw::DebugDraw(uint32 drawFlags)
{
	m_drawFlags = drawFlags;
}
DebugDraw::~DebugDraw()
{
}
void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
}
void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
}
void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
	SDL_Renderer*renderer = TheDirector::getInstance()->getRenderer()->getSDL_Renderer();
	Uint8 r = color.r * 255;
	Uint8 g = color.g * 255;
	Uint8 b = color.b * 255;
	Sint16 x = center.x *32;
	Sint16 y = center.y * 32;
	Sint16 radius1 = radius * 32;
	circleRGBA(renderer,x,y,radius1,r,g,b,0xff);
}
void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
	DrawCircle(center,radius,color);
}
void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
}
void DebugDraw::DrawTransform(const b2Transform& xf)
{
}