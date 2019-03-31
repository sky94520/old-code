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

//SDL ���ں���Ⱦ��
SDL_Window* gWin = nullptr;
SDL_Renderer* gRen = nullptr;
//OpenGL��������
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
	//��������
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	gWin = SDL_CreateWindow("OpenGL",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,480,SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	gRen = SDL_CreateRenderer(gWin,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	//����GL����
	gContext = SDL_GL_CreateContext(gWin);
	//����ÿ�θ�������ʱ�����Ļ��������
	SDL_GL_SetSwapInterval(1);

	return true;
}

bool initGL(GLsizei w, GLsizei h)
{
	bool success = true;
	GLenum error = GL_NO_ERROR;
	GLfloat nRange = 100.f;

	glViewport(0, 0, w, h);
	//��ʼ��
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
	//����ˢ����ɫ
	glClearColor(0.f, 1.f, 1.f, 1.f);
	//��ɫģʽ����Ϊ��ɫģʽGL_FLAT 
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
	//��־�����ɫ
	int iPivot = 1;
	GLboolean bCull = false, bDepth = true, bOutline = false;
	//������ں���Ȼ�����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//��־ ��ѡ��
	if (bCull)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);
	//��Ȳ���
	if (bDepth)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
	//���Ʊ��� ֻ��Ϊ�߿�
	if (bOutline)
		glPolygonMode(GL_BACK, GL_LINE);
	else
		glPolygonMode(GL_BACK, GL_FILL);
	//�������״̬��������ת
	glPushMatrix();
	glRotatef(xRot, 1.f, 0.f, 0.f);
	glRotatef(yRot, 0.f, 1.f, 0.f);
	//��ʼ������������
	glBegin(GL_TRIANGLE_FAN);
	//Բ׶
	glVertex3f(0.f, 0.f, 75.f);

	for (angle = 0.f; angle < (2.f * GL_PI); angle += (GL_PI / 8.f))
	{
		x = 50.f * sin(angle);
		y = 50.f * cos(angle);
		//����ʹ�ú�ɫ����ɫ
		if (iPivot++ % 2 == 0)
			glColor3f(0.f, 1.f, 0.f);
		else
			glColor3f(1.f, 0.f, 0.f);
		//Ϊ��������ָ����һ������
		glVertex2f(x, y);
	}
	glEnd();
	//��ʼ����һ���µ���������
	glBegin(GL_TRIANGLE_FAN);
	//�����ȵ�����λ��ԭ��
	glVertex2f(0.f, 0.f);

	for (angle = 0.f; angle <= 2.f * GL_PI; angle += GL_PI / 8.f)
	{
		x = 50.f * sin(angle);
		y = 50.f * cos(angle);
		//����ʹ�ð�ɫ�ͺ�ɫ
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