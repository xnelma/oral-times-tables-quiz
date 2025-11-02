#ifndef OTTQ_20250830_0958_INCLUDE
#define OTTQ_20250830_0958_INCLUDE

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

#endif // OTTQ_20250830_0958_INCLUDE
