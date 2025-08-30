#include "tts_language_settings.hpp"
#include "auto_locale.hpp"
#include <QDir>
#include <algorithm>

Tts::LanguageSettings::LanguageSettings() : isInAutoMode_(true), index_(0)
{
    loadMode();
    loadLocaleDescriptors();
    loadIndex();
}

void Tts::LanguageSettings::loadMode()
{
    isInAutoMode_ = loadAutoLocaleSetting();
}

void Tts::LanguageSettings::loadLocaleDescriptors()
{
    if (localeDescriptors_.size() > 0) // Cannot change without an app update.
        return;

    auto qmFiles = QDir(qmDirPath).entryList({ "*.qm" });
    auto extractLocale = [](const QString &fileName) -> LocaleDescriptor {
        QString localeName = fileName;
        localeName.replace(qmLocaleNameRegex, "\\1\\2");

        QLocale mlocale = QLocale(localeName);
        // Create a locale object to do the parsing, instead of passing on
        // invalid locale names to be used for QLocale objects later on.

        return LocaleDescriptor(mlocale);
    };

    // C++20
    std::ranges::transform(
        qmFiles,
        std::back_inserter(localeDescriptors_), // push_back, so in O(1)
        extractLocale);
}

void Tts::LanguageSettings::loadIndex()
{
    auto setIndex = [this](std::vector<LocaleDescriptor>::iterator index) {
        // Because I don't expect large translation resource lists, the type
        // of index_ doesn't need to be long:
        // NOLINTNEXTLINE(*-narrowing-conversions)
        index_ = std::distance(localeDescriptors_.begin(), index);
    };

    LocaleDescriptor savedKey = loadLocaleSetting();
    auto it = std::ranges::find(localeDescriptors_, savedKey);
    if (it != localeDescriptors_.end()) {
        setIndex(it);
        return;
    }

    // Alternatively set to a locale for a different territory.
    auto sameLanguage = [savedKey](const LocaleDescriptor &lk) -> bool {
        return lk.language == savedKey.language;
    };
    it = std::ranges::find_if(localeDescriptors_, sameLanguage);
    if (it != localeDescriptors_.end()) {
        setIndex(it);
    } else {
        // If no alternative was found, use the first language in the list.
        index_ = 0;
    }

    saveLocaleSetting(indexDescriptor());
    // Save already on setup, so if the SettingsView gets left without
    // switching back to Auto and without selecting anything else, the
    // language highlighted in the list is actually used.
}

QStringList Tts::LanguageSettings::availableLanguages()
{

    // The translation resource list cannot change without an app update.
    if (languages_.size() > 0)
        return languages_;

    if (localeDescriptors_.size() == 0)
        loadLocaleDescriptors();

    // C++20
    std::ranges::transform(
        localeDescriptors_,
        std::back_inserter(languages_),
        [](const LocaleDescriptor &key) -> QString {
            return QLocale(key.language, key.territory).nativeLanguageName();
        });

    return languages_;
}

int Tts::LanguageSettings::index()
{
    return index_;
}

bool Tts::LanguageSettings::isInAutoMode()
{
    return isInAutoMode_ || index_ < 0 || index_ >= localeDescriptors_.size();
}

void Tts::LanguageSettings::setIndex(const int i)
{
    index_ = i;
    saveLocaleSetting(indexDescriptor());
}

void Tts::LanguageSettings::setToAutoMode()
{
    isInAutoMode_ = true;
    saveAutoLocaleSetting(isInAutoMode_);
}

void Tts::LanguageSettings::setToManualMode()
{
    isInAutoMode_ = false;
    saveAutoLocaleSetting(isInAutoMode_);
}

auto Tts::LanguageSettings::indexDescriptor() -> LocaleDescriptor
{
    if (index_ < 0 || index_ >= localeDescriptors_.size())
        return LocaleDescriptor(autoLocale());
    // When in auto mode, the list can still get shown in the UI, so the index
    // and the corresponding LocaleDescriptor are still needed.

    return localeDescriptors_[index_];
}
