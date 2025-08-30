#include "tts_rate_settings.hpp"

Tts::VoiceRateSettings::VoiceRateSettings() : rate_(loadVoiceRateSetting()) { }

double Tts::VoiceRateSettings::load()
{
    return rate_;
}

void Tts::VoiceRateSettings::save(const double rate)
{
    rate_ = rate;
    saveVoiceRateSetting(rate_);
}
