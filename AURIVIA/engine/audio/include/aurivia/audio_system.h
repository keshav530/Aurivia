#pragma once

#include <glm/glm.hpp>
#include <string>

namespace Aurivia {

/**
 * @brief Audio system for sound playback and management
 */
class AudioSystem
{
public:
    AudioSystem();
    ~AudioSystem();
    
    bool Initialize();
    void Shutdown();
    
    // Audio playback
    uint32_t LoadSound(const std::string& filepath);
    uint32_t LoadMusic(const std::string& filepath);
    
    void PlaySound(uint32_t soundID, float volume = 1.0f);
    void PlayMusic(uint32_t musicID, float volume = 1.0f, bool loop = true);
    
    void StopSound(uint32_t soundID);
    void StopMusic();
    void PauseMusic();
    void ResumeMusic();
    
    // Volume control
    void SetMasterVolume(float volume);
    void SetSoundVolume(uint32_t soundID, float volume);
    void SetMusicVolume(float volume);
    
    // 3D audio
    void SetListenerPosition(const glm::vec3& position);
    void SetListenerOrientation(const glm::vec3& forward, const glm::vec3& up);
    void SetSoundPosition(uint32_t soundID, const glm::vec3& position);

private:
    // OpenAL context
    void* m_device;
    void* m_context;
    bool m_isInitialized;
    
    // Audio state
    float m_masterVolume;
    float m_musicVolume;
    uint32_t m_currentMusicID;
};

} // namespace Aurivia
