#include<map>
#pragma once
class TextureManager
{
  private:
	std::map < std::string, SDL_Texture * >m_textureMap;
	static TextureManager*s_pInstance;
  public:
  TextureManager();
  ~TextureManager();
  static TextureManager* Instance();
  
	bool load(std::string fileName, std::string id, SDL_Renderer * pRenderer);
	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer * pRenderer,
			  SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow,
				   int currentFrame, SDL_Renderer * pRenderer, SDL_RendererFlip flip =
				   SDL_FLIP_NONE);
};
TextureManager*TextureManager::s_pInstance = NULL;
TextureManager::TextureManager()
{
}
TextureManager::~TextureManager()
{
}
TextureManager*TextureManager::Instance()
{
	if (s_pInstance == NULL)
	{
		s_pInstance = new TextureManager();
		return s_pInstance;
	}
	return s_pInstance;
}
bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer * pRenderer)
{
	SDL_Texture *pTexture = IMG_LoadTexture(pRenderer, fileName.c_str());
	// everything went ok,add the texture to our list
	if (pTexture != NULL)
	{
		m_textureMap[id] = pTexture;
		return true;
	}
	// reaching here means something went wrong
	return false;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height,
						  SDL_Renderer * pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow,
							   int currentFrame, SDL_Renderer * pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1);
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0,flip);
}
