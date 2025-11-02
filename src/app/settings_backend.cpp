#include "settings_backend.hpp"
#include "tts/auto_locale.hpp"

SettingsBackend::SettingsBackend(QObject *parent) : QObject(parent) { }

QStringList SettingsBackend::languages()
{
    return languageSettings_.availableLanguages();
}

int SettingsBackend::languageIndex()
{
    return languageSettings_.index();
}

bool SettingsBackend::useAutoTtsLanguage()
{
    return languageSettings_.isInAutoMode();
}

auto SettingsBackend::autoLanguage() -> LanguageName
{
    LanguageName l(Tts::autoLocale());
    return l;
}

double SettingsBackend::voiceRate()
{
    return voiceRateSettings_.load();
}

void SettingsBackend::setLanguageIndex(const int index)
{
    languageSettings_.setIndex(index);

    emit languageIndexChanged();
}

void SettingsBackend::setUseAutoTtsLanguage(const bool useAutoTtsLanguage)
{
    if (useAutoTtsLanguage)
        languageSettings_.setToAutoMode();
    else
        languageSettings_.setToManualMode();

    emit useAutoTtsLanguageChanged();
}

void SettingsBackend::setVoiceRate(const double rate)
{
    voiceRateSettings_.save(rate);
}
