#ifndef TTS_RATE_SETTINGS_HPP
#define TTS_RATE_SETTINGS_HPP

#include "tts_settings.hpp"

namespace Tts {

class VoiceRateSettings : Settings
{
public:
    VoiceRateSettings();

    double load();
    void save(const double rate);

private:
    double rate_;
};

} // namespace Tts

#endif // TTS_RATE_SETTINGS_HPP
