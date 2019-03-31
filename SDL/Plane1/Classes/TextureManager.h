#ifndef __TextureManager_H__
#define __TextureManager_H__

#include<iostream>
#include<map>
#include<string>
#include<stdexcept>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
//管理图片的单例类
class TextureManager
{
  private:
    //键值保存SDL_Texture
	std::map < std::string, SDL_Texture * >m_textureMap;
	static TextureManager*s_pInstance;
	//保存的render。因为一个程序一般情况下只有一个窗口
	static SDL_Renderer*m_pRenderer;
	TextureManager();
  public:
  ~TextureManager();
  static TextureManager* Instance();
  //绑定render
  static void bind(SDL_Renderer*ren);
  //加载图片
  bool load(std::string fileName, std::string id);
  //画出某一帧
  void draw(std::string id, int x, int y, int width, int height,SDL_RendererFlip flip = SDL_FLIP_NONE);
  void drawFrame(std::string id, int x, int y, int width, int height, int currentRow,int currentFrame,double angle,int alpha, SDL_RendererFlip flip =SDL_FLIP_NONE);
  //从map中清除id的Texture
  void clearFromTextureMap(std::string id);

  void drawTile(std::string id,int margin,int spacing,int x,int y,int width,int height,int currentRow,int currentFrame);
  std::map<std::string,SDL_Texture*> & getTextureMap()
  {
  	return m_textureMap;
  }
};

typedef TextureManager TheTextureManager;
#endif
