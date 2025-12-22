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
    // TODO set to auto mode for invalid index
    return settings_.loadAutoLocaleSetting();
}

auto SettingsBackend::autoLanguage() -> LanguageName
{
    LanguageName l(Tts::autoLocale());
    return l;
}

double SettingsBackend::voiceRate()
{
    return settings_.loadVoiceRateSetting();
}

void SettingsBackend::setLanguageIndex(const int index)
{
    if (languageIndex() == index)
        return;

    settings_.saveLocaleSetting(Tts::TranslationResources::locale(index));
    emit languageIndexChanged();
}

void SettingsBackend::setUseAutoTtsLanguage(const bool useAutoTtsLanguage)
{
    if (SettingsBackend::useAutoTtsLanguage() == useAutoTtsLanguage)
        return;

    settings_.saveAutoLocaleSetting(useAutoTtsLanguage);
    emit useAutoTtsLanguageChanged();
}

void SettingsBackend::setVoiceRate(const double rate)
{
    if (SettingsBackend::voiceRate() == rate)
        return;

    settings_.saveVoiceRateSetting(rate);
    emit voiceRateChanged();
}
