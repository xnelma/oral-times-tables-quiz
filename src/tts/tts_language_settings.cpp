#include "tts_language_settings.hpp"
#include "auto_locale.hpp"
#include "self_updating_translator.hpp"
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
    // Should not be static because of unit testing.
    const ResourceMap resources = SelfUpdatingTranslator::resources();
    const ResourceMap::const_iterator itBegin = resources.begin();

    LocaleDescriptor savedKey = loadLocaleSetting();
    auto itKey = resources.find(savedKey);
    if (itKey != resources.end()) {
        setIndex(std::distance(itBegin, itKey));
        return;
    }

    // Alternatively set to a locale for a different territory.
    auto sameLanguage = [savedKey](const ResourcePair &r) -> bool {
        return r.first.language == savedKey.language;
    };
    itKey = std::ranges::find_if(resources, sameLanguage);
    if (itKey != resources.end()) {
        setIndex(std::distance(itBegin, itKey));
        return;
    }

    // If no alternative was found, use the first language in the list.
    setIndex(0);
}

QStringList Tts::LanguageSettings::availableLanguages()
{
    // The translation resource list cannot change without an app update.
    if (languages_.size() > 0)
        return languages_;

    // C++20
    std::ranges::transform(
        SelfUpdatingTranslator::resources(),
        std::back_inserter(languages_),
        [](const ResourcePair &key) -> QString {
            LocaleDescriptor ld = key.first;
            return QLocale(ld.language, ld.territory).nativeLanguageName();
        });

    return languages_;
}

long Tts::LanguageSettings::index()
{
    return index_;
}

bool Tts::LanguageSettings::isInAutoMode()
{
    const auto resourcesSize = SelfUpdatingTranslator::resources().size();

    return isInAutoMode_ || index_ < 0 || index_ >= resourcesSize;
}

void Tts::LanguageSettings::setIndex(const long i)
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
    auto resources = SelfUpdatingTranslator::resources();

    if (index_ < 0 || index_ >= resources.size())
        return autoLocale();
    // When in auto mode, the list can still get shown in the UI, so the index
    // and the corresponding LocaleDescriptor are still needed.

    ResourceMap::iterator it = resources.begin();
    std::advance(it, index_);

    return it->first;
}
