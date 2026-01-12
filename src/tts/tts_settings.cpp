#include "tts_settings.hpp"

Tts::Settings::Settings() { }

auto Tts::Settings::loadLocaleSetting() -> LocaleDescriptor
{
    return LocaleDescriptor(
        settings_.value(SettingsKeys::language, SettingsDefaults::language)
            .value<QLocale::Language>(),
        settings_.value(SettingsKeys::territory, SettingsDefaults::territory)
            .value<QLocale::Territory>());
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

auto Tts::Settings::getAutoLocale() -> LocaleDescriptor &
{
    autoLocale_ = Tts::AutoLocale();
    return autoLocale_;
}
