#include "tts_settings.hpp"

Tts::Settings::Settings() { }

auto Tts::Settings::loadLocaleSetting() -> LocaleDescriptor
{
    auto l = settings_.value(SettingsKeys::language, SettingsDefaults::language)
                 .value<QLocale::Language>();
    auto t =
        settings_.value(SettingsKeys::territory, SettingsDefaults::territory)
            .value<QLocale::Territory>();
    return LocaleDescriptor(l, t);
}

bool Tts::Settings::loadAutoLocaleSetting()
{
    return settings_
        .value(SettingsKeys::autoLocale, SettingsDefaults::autoLocale)
        .toBool();
}

double Tts::Settings::loadVoiceRateSetting()
{
    return settings_.value(SettingsKeys::voiceRate, SettingsDefaults::voiceRate)
        .toDouble();
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
