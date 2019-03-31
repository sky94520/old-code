#include "SoundManager.h"

SoundManager*SoundManager::s_pInstance = NULL;
//private
SoundManager::SoundManager()
{
    //初始化其他扩展格式 ogg
    //Mix_Init(MIX_INIT_OGG);
    //只是用于初始化wav格式AUDIO_S16
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,2048);
//    if(Mix_Init(MIX_INIT_MP3) == 0)
//    std::cout<<"init error:"<<Mix_GetError()<<std::endl;
}
//private
SoundManager::~SoundManager()
{
    //delete
    Mix_CloseAudio();
    //Mix_Quit();
}
//public
SoundManager*SoundManager::Instance()
{
    if(s_pInstance == NULL)
        s_pInstance = new SoundManager();
    return s_pInstance;
}
bool SoundManager::load(std::string fileName,std::string id,sound_type type)
{
    //如果是music
    if(type == SOUND_MUSIC)
    {
        Mix_Music*pMusic = Mix_LoadMUS(fileName.c_str());
        //抛出错误
        if(pMusic == NULL)
        {
            throw std::
            runtime_error(fileName + " load error: " + Mix_GetError());
        }
        m_music[id] = pMusic;
        std::cout<<"load music:"<<id<<"\n";
        return true;
    }
    else if(type == SOUND_SFX)
    {
        Mix_Chunk*pChunk = Mix_LoadWAV(fileName.c_str());
        if(pChunk == NULL)
        {
            throw std::runtime_error(fileName +" load error: " + Mix_GetError());
        }
        m_sfxs[id] = pChunk;
        std::cout<<"load sfx:"<<id<<"\n";
        return true;
    }
    return false;
}
void SoundManager::playMusic(std::string id,int loop)
{
    Mix_PlayMusic(m_music[id],loop);
}
void SoundManager::playSound(std::string id,int loop)
{
    Mix_PlayChannel(-1,m_sfxs[id],loop);
}
