#include "settings_backend.hpp"
#include "tts/auto_locale_descriptor.hpp"
#include "tts/translation_resources.hpp"
#include <QtLogging>
#include <stdexcept>
#include <algorithm>

SettingsBackend::SettingsBackend(QObject *parent) : QObject(parent) { }

QStringList SettingsBackend::languages()
{
    static QStringList languageNames;
    if (languageNames.size() > 0)
        return languageNames;

    std::ranges::transform( // C++20
        Tts::TranslationResources::getLanguageNames(),
        std::back_inserter(languageNames),
        [](const std::string &s) -> QString {
            return QString::fromStdString(s);
        });

    return languageNames;
}

int SettingsBackend::languageIndex()
{
    Tts::LocaleDescriptor localeKey = settings_.loadLocaleSetting();
    // Because I don't expect large translation resource lists, the type
    // of index_ doesn't need to be long:
    // NOLINTNEXTLINE(*-narrowing-conversions)
    int index = Tts::TranslationResources::index(localeKey);
    if (index < 0) {
        setUseAutoTtsLanguage(true);
        return 0;
    }
    return index;
}

bool SettingsBackend::useAutoTtsLanguage()
{
    return settings_.loadAutoLocaleSetting();
}

auto SettingsBackend::autoLanguage() -> LanguageName
{
    Tts::AutoLocaleDescriptor l;
    LanguageName languageName(l);
    return languageName;
}

double SettingsBackend::voiceRate()
{
    return settings_.loadVoiceRateSetting();
}

void SettingsBackend::setLanguageIndex(const int index)
{
    if (languageIndex() == index)
        return;

    try {
        Tts::LocaleDescriptor ld = Tts::TranslationResources::locale(index);
        settings_.saveLocaleSetting(ld);
        emit languageIndexChanged();
    } catch (const std::invalid_argument &e) {
        qInfo() << "Could not set index:" << e.what();
    }
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
