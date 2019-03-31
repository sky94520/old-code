#include<iostream>
#include<cmath>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_opengl.h"

bool init();
bool initGL(GLsizei w, GLsizei h);
void update();
void render();
void handleEvents(SDL_Event* event);
void close();

#define GL_PI 3.1415f

//SDL 窗口和渲染器
SDL_Window* gWin = nullptr;
SDL_Renderer* gRen = nullptr;
//OpenGL的上下文
SDL_GLContext gContext;
bool gQuit = false;
GLubyte fire[] = {
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xc0,
	0x00, 0x00, 0x01, 0xf0,
	0x00, 0x00, 0x07, 0xf0,
	0x00, 0x00, 0x1f, 0xe0,
	0x00, 0x00, 0x1f, 0xc0,
	0x00, 0x00, 0x3f, 0x80,
	0x00, 0x00, 0x7e, 0x00,
	0x00, 0x00, 0xff, 0x80,
	0x00, 0x00, 0xff, 0xe0,
	0x00, 0x00, 0xff, 0xf8,
	0x00, 0x00, 0xff, 0xe8,
	0x00, 0x00, 0xbf, 0x78,
	0x00, 0x00, 0xb7, 0x00,
	0x71, 0x10, 0x4a, 0x80,
	0x03, 0x10, 0x4e, 0x80,
	0x02, 0x88, 0x8c, 0x20,
	0x05, 0x05, 0x04, 0x04,
	0x02, 0x82, 0x14, 0x40,
	0x02, 0x40, 0x10, 0x80,
	0x02, 0x64, 0x1a, 0x80,
	0x00, 0x92, 0x29, 0x00,
	0x00, 0xb0, 0x48, 0x00,
	0x00, 0xc8, 0x90, 0x00,
	0x00, 0x85, 0x10, 0x00,
	0x00, 0x03, 0x00, 0x00,
	0x00, 0x00, 0x10, 0x00,};

GLfloat xRot = 0.f, yRot = 0.f;
GLboolean bLBClicked = false;

int main(int argc, char** argv)
{
	SDL_Event event;
	
	init();
	initGL(800, 480);

	while(!gQuit)
	{
		update();
		render();

		SDL_GL_SwapWindow(gWin);

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT: gQuit = true; break;

			default:
				handleEvents(&event);
				break;
			}
		}
	}
	close();

	return 0;
}
bool init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	//设置属性
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	gWin = SDL_CreateWindow("OpenGL",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,480,SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	gRen = SDL_CreateRenderer(gWin,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	//设置GL环境
	gContext = SDL_GL_CreateContext(gWin);
	//设置每次更换缓存时跳过的缓存个数。
	SDL_GL_SetSwapInterval(1);

	return true;
}

bool initGL(GLsizei w, GLsizei h)
{
	bool success = true;
	GLenum error = GL_NO_ERROR;
	GLfloat nRange = 100.f;

	glViewport(0, 0, w, h);
	//初始化
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	GLfloat aspectRatio = 0.f;
	aspectRatio = (GLfloat)w / (GLfloat)h;

	if (w <= h)
		glOrtho(-nRange, nRange, -nRange / aspectRatio, nRange / aspectRatio, -nRange, -nRange);
	else
		glOrtho(-nRange * aspectRatio, nRange * aspectRatio, -nRange, nRange, -nRange, nRange);
	//glOrtho(0.0, w, 0, h, 1.0, -1.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//设置刷新颜色
	glClearColor(0.f, 0.f, 0.f, 0.f);

	//glColor3f(1.f, 0.f, 0.f);
	//启用多边形点画模式
	//glEnable(GL_POLYGON_STIPPLE);
	//指定一个特定的点画模式
	//glPolygonStipple(fire);

	return success;
}

void update()
{
}

void render()
{
	GLboolean bEdgeFlag = true;
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	glRotatef(xRot, 1.f, 0.f, 0.f);
	glRotatef(yRot, 0.f, 1.f, 0.f);

	glBegin(GL_TRIANGLES);
		glEdgeFlag(bEdgeFlag);
		glVertex2f(-20.f, 0.f);
		glEdgeFlag(true);
		glVertex2f(20.f, 0.f);
		glVertex2f(0.f, 40.f);

		glVertex2f(-20.f, 0.f);
		glVertex2f(-60.f, -20.f);
		glEdgeFlag(bEdgeFlag);
		glVertex2f(-20.f, -40.f);
		glEdgeFlag(true);

		glVertex2f(-20.f, -40.f);
		glVertex2f(0.f, -80.f);
		glEdgeFlag(bEdgeFlag);
		glVertex2f(20.f, -40.f);
		glEdgeFlag(true);

		glVertex2f(20.f, -40.f);
		glVertex2f(60.f, -20.f);
		glEdgeFlag(bEdgeFlag);
		glVertex2f(20.f, 0.f);
		glEdgeFlag(true);

		glEdgeFlag(bEdgeFlag);
		glVertex2f(-20.f, 0.f);
		glVertex2f(-20.f, -40.f);
		glVertex2f(20.f, 0.f);

		glVertex2f(-20.f, -40.f);
		glVertex2f(20.f, -40.f);
		glVertex2f(20.f, 0.f);
		glEdgeFlag(true);
	glEnd();

	glPopMatrix();
}

void handleEvents(SDL_Event* event)
{
	switch (event->type)
	{
	case SDL_MOUSEBUTTONDOWN:bLBClicked = true; break;
	case SDL_MOUSEBUTTONUP:bLBClicked = false; break;
	case SDL_MOUSEMOTION:
		{
			if (bLBClicked)
			{
				xRot += event->motion.xrel;
				yRot += event->motion.yrel;
			}
		}break;
	}
}

void close()
{
}