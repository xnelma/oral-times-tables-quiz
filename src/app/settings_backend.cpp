#include "settings_backend.hpp"
#include "tts/auto_locale.hpp"
#include "tts/translation_resources.hpp"

SettingsBackend::SettingsBackend(QObject *parent) : QObject(parent) { }

QStringList SettingsBackend::languages()
{
    return Tts::TranslationResources::getLanguageNames();
}

int SettingsBackend::languageIndex()
{
    Tts::LocaleDescriptor localeKey = settings_.loadLocaleSetting();
    // Because I don't expect large translation resource lists, the type
    // of index_ doesn't need to be long:
    // NOLINTNEXTLINE(*-narrowing-conversions)
    int index = Tts::TranslationResources::index(localeKey);
    // TODO handle index < 0
    return index;
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
