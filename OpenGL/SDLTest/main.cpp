#include<iostream>
#include<cmath>

//#include "kazmath\kazmath.h"
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
	glClearColor(0.f, 1.f, 1.f, 1.f);
	//着色模式设置为单色模式GL_FLAT 
	glShadeModel(GL_SMOOTH);
	glFrontFace(GL_CW);

	return success;
}

void update()
{
}

void render()
{
	GLfloat x,y,angle;
	//标志替代颜色
	int iPivot = 1;
	GLboolean bCull = false, bDepth = true, bOutline = false;
	//清除窗口和深度缓冲区
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//标志 打开选择
	if (bCull)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);
	//深度测试
	if (bDepth)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
	//绘制背面 只作为线框
	if (bOutline)
		glPolygonMode(GL_BACK, GL_LINE);
	else
		glPolygonMode(GL_BACK, GL_FILL);
	//保存矩阵状态并进行旋转
	glPushMatrix();
	glRotatef(xRot, 1.f, 0.f, 0.f);
	glRotatef(yRot, 0.f, 1.f, 0.f);
	//开始绘制三角形扇
	glBegin(GL_TRIANGLE_FAN);
	//圆锥
	glVertex3f(0.f, 0.f, 75.f);

	for (angle = 0.f; angle < (2.f * GL_PI); angle += (GL_PI / 8.f))
	{
		x = 50.f * sin(angle);
		y = 50.f * cos(angle);
		//交替使用红色和绿色
		if (iPivot++ % 2 == 0)
			glColor3f(0.f, 1.f, 0.f);
		else
			glColor3f(1.f, 0.f, 0.f);
		//为三角形扇指定下一个顶点
		glVertex2f(x, y);
	}
	glEnd();
	//开始绘制一个新的三角形扇
	glBegin(GL_TRIANGLE_FAN);
	//三角扇的中心位于原点
	glVertex2f(0.f, 0.f);

	for (angle = 0.f; angle <= 2.f * GL_PI; angle += GL_PI / 8.f)
	{
		x = 50.f * sin(angle);
		y = 50.f * cos(angle);
		//交替使用白色和黑色
		if (iPivot++ % 2 == 0)
			glColor3f(1.f, 1.f, 1.f);
		else
			glColor3f(0.f, 0.f, 0.f);

		glVertex2f(x, y);
	}
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