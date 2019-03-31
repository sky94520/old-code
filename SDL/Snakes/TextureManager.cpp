#include "TextureManager.h"
#include "Game.h"

TextureManager *TextureManager::s_pInstance = NULL;

TextureManager::TextureManager() {
}
TextureManager::~TextureManager() {
}
TextureManager *TextureManager::Instance() {
  if (s_pInstance == NULL)
  {
    s_pInstance = new TextureManager();
    return s_pInstance;
  }
  return s_pInstance;
}
void TextureManager::bind(SDL_Renderer * ren) {
  m_pRenderer = ren;
}
bool TextureManager::load(std::string fileName, std::string id) {
  auto name = m_textureMap.find(id);
  if (name != m_textureMap.end()) {
    std::cout << id << ":已存在" << "\n";
    return false;
  }
  SDL_Texture *pTexture = IMG_LoadTexture(m_pRenderer, fileName.c_str());
  // everything went ok,add the texture to our list
  if (pTexture != NULL) {
    m_textureMap[id] = pTexture;
    return true;
  }
  // reaching here means something went wrong
  else
    throw std::runtime_error(SDL_GetError());
}

void TextureManager::draw(std::string id, int x, int y, int width, int height,
                          SDL_RendererFlip flip) {
  std::map < std::string, SDL_Texture * >::iterator iter_tex =
    m_textureMap.find(id);
  if (iter_tex == m_textureMap.end()) {
    std::cout << "error:" << id << "not exist" << std::endl;
    return;
  }
  // std::cout<<"png"<<id<<std::endl;
  SDL_Rect srcRect;
  SDL_Rect destRect;
  srcRect.x = 0;
  srcRect.y = 0;
  srcRect.w = destRect.w = width;
  srcRect.h = destRect.h = height;
  destRect.x = x;
  destRect.y = y;
  SDL_RenderCopyEx(m_pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0,
                   flip);
}
void TextureManager::draw(std::string id, SDL_Rect*clip,SDL_Rect*dest,double angle , SDL_RendererFlip flip)
{
  std::map < std::string, SDL_Texture * >::iterator iter_tex =
    m_textureMap.find(id);
  if (iter_tex == m_textureMap.end())
  {
    std::cout << "error:" << id << "not exist" << std::endl;
    return;
  }
  SDL_RenderCopyEx(m_pRenderer, m_textureMap[id],clip,dest, angle, NULL,
                   flip);
}
void TextureManager::update()
{
}
SDL_Texture *TextureManager::getTextureById(std::string id)
{
  auto it = m_textureMap.find(id);
  /* 如果无此id,返回NULL */
  if (it == m_textureMap.end())
    return NULL;
  return m_textureMap[id];
}
/*void TextureManager::drawFrame(std::string id, int x, int y,
                                                int width, int height,
                                                int currentRow,
                                                int currentFrame,
                                                SDL_RendererFlip flip)
{
  SDL_Rect srcRect;
  SDL_Rect destRect;
  srcRect.x = width * currentFrame;
  srcRect.y = height * (currentRow - 1);
  srcRect.w = destRect.w = width;
  srcRect.h = destRect.h = height;
  destRect.x = x;
  destRect.y = y;

  SDL_RenderCopyEx(m_pRenderer, m_textureMap[id], &srcRect, &destRect,
                   0, NULL, flip);
}
*/
void TextureManager::clearFromTextureMap(std::string id)
{
  m_textureMap.erase(id);
}
