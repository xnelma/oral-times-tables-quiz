#include "tts_settings.hpp"
#include <QLocale>

Tts::Settings::Settings() { }

auto Tts::Settings::loadLocaleSetting() -> LocaleDescriptor
{
    auto l = settings_.value(SettingsKeys::language, QLocale::AnyLanguage)
                 .value<QLocale::Language>();
    auto t = settings_.value(SettingsKeys::territory, QLocale::AnyTerritory)
                 .value<QLocale::Territory>();
    return LocaleDescriptor(l, t);
}

bool Tts::Settings::loadAutoLocaleSetting()
{
    return settings_.value(SettingsKeys::autoLocale, true).toBool();
}

double Tts::Settings::loadVoiceRateSetting()
{
    return settings_.value(SettingsKeys::voiceRate, 0).toDouble();
}

void Tts::Settings::saveLocaleSetting(const LocaleDescriptor &ld)
{
    settings_.setValue(SettingsKeys::language, ld.language);
    settings_.setValue(SettingsKeys::territory, ld.territory);
}

void Tts::Settings::saveAutoLocaleSetting(const bool useAutoLocale)
{
    settings_.setValue(SettingsKeys::autoLocale, useAutoLocale);
}

void Tts::Settings::saveVoiceRateSetting(const double rate)
{
    settings_.setValue(SettingsKeys::voiceRate, rate);
}
