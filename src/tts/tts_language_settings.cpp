#include "tts_language_settings.hpp"
#include "auto_locale.hpp"
#include "translator_resources.hpp"
#include <QDir>
#include <algorithm>
#include <iterator>

Tts::LanguageSettings::LanguageSettings() : isInAutoMode_(true), index_(0)
{
    loadMode();
    loadIndex();
}

void Tts::LanguageSettings::loadMode()
{
    isInAutoMode_ = loadAutoLocaleSetting();
}

void Tts::LanguageSettings::loadIndex()
{
    static const auto resources = Tts::Translator::resources();

    auto setIndex = [this](Tts::ResourceMap::const_iterator index) {
        // Because I don't expect large translation resource lists, the type
        // of index_ doesn't need to be long:
        // NOLINTNEXTLINE(*-narrowing-conversions)
        index_ = std::distance(resources.begin(), index);
    };

    LocaleDescriptor savedKey = loadLocaleSetting();
    auto it = resources.find(savedKey);
    if (it != resources.end()) {
        setIndex(it);
        return;
    }

    // Alternatively set to a locale for a different territory.
    auto sameLanguage = [savedKey](const Tts::ResourcePair &r) -> bool {
        return r.first.language == savedKey.language;
    };
    it = std::ranges::find_if(resources, sameLanguage);
    if (it != resources.end()) {
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

    // C++20
    std::ranges::transform(
        Tts::Translator::resources(),
        std::back_inserter(languages_),
        [](const Tts::ResourcePair &key) -> QString {
            LocaleDescriptor ld = key.first;
            return QLocale(ld.language, ld.territory).nativeLanguageName();
        });

    return languages_;
}

int Tts::LanguageSettings::index()
{
    return index_;
}

bool Tts::LanguageSettings::isInAutoMode()
{
    static const auto resourcesSize = Tts::Translator::resources().size();

    return isInAutoMode_ || index_ < 0 || index_ >= resourcesSize;
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
    static auto resources = Tts::Translator::resources();

    if (index_ < 0 || index_ >= resources.size())
        return LocaleDescriptor(autoLocale());
    // When in auto mode, the list can still get shown in the UI, so the index
    // and the corresponding LocaleDescriptor are still needed.

    Tts::ResourceMap::iterator it = resources.begin();
    std::advance(it, index_);

    return it->first;
}
