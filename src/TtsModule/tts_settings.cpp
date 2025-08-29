#include "tts_settings.hpp"

Tts::Settings::Settings()
    : languageKey_("TtsLocale/language"),
      territoryKey_("TtsLocale/territory"),
      autoLocaleKey_("TtsLocale/useAutoLocale"),
      voiceRateKey_("Tts/voiceRate")
{
}

auto Tts::Settings::loadLocaleSetting() -> LocaleDescriptor
{
    auto l = settings_.value(languageKey_, 0 /*QLocale::AnyLanguage*/)
                 .value<QLocale::Language>();
    auto t = settings_.value(territoryKey_, 0 /*QLocale::AnyTerritory*/)
                 .value<QLocale::Territory>();
    return LocaleDescriptor(l, t);
}

bool Tts::Settings::loadAutoLocaleSetting()
{
    return settings_.value(autoLocaleKey_, true).toBool();
}

double Tts::Settings::loadVoiceRateSetting()
{
    return settings_.value(voiceRateKey_, 1.0).toDouble();
}

void Tts::Settings::saveLocaleSetting(const LocaleDescriptor &ld)
{
    settings_.setValue(languageKey_, ld.language);
    settings_.setValue(territoryKey_, ld.territory);
}

void Tts::Settings::saveAutoLocaleSetting(const bool useAutoLocale)
{
    settings_.setValue(autoLocaleKey_, useAutoLocale);
}

void Tts::Settings::saveVoiceRateSetting(const double voiceRate)
{
    settings_.setValue(voiceRateKey_, voiceRate);
}
