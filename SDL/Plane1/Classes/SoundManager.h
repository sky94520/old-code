#ifndef __SoundManager_H__
#define __SoundManager_H__

#include<iostream>
#include<string>
#include<map>
#include<stdexcept>

#define OGG_MUSIC
#include "SDL2/SDL_mixer.h"

enum sound_type
{
    SOUND_MUSIC = 0,
    SOUND_SFX = 1
};
class SoundManager
{
private:
    static SoundManager*s_pInstance;
    //save music's files
    std::map<std::string,Mix_Chunk*> m_sfxs;
    std::map<std::string,Mix_Music*> m_music;
private:
    SoundManager();
    ~SoundManager();
public:
    static SoundManager*Instance();
    bool load(std::string fileName,std::string id,sound_type type);
    void playSound(std::string id,int loop);
    void playMusic(std::string id, int loop);

    void clearFromSfxMap(std::string id);
    void clearFromMusicMap(std::string id);
};
typedef SoundManager TheSoundManager;
#endif
