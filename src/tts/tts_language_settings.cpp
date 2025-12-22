#include "tts_language_settings.hpp"
#include "auto_locale.hpp"
#include "translation_resources.hpp"
#include <QDir>

Tts::LanguageSettings::LanguageSettings()
    : isInAutoMode_(loadAutoLocaleSetting()), index_(-1)
{
}

long Tts::LanguageSettings::index()
{
    if (index_ > -1)
        return index_;

    // Should not be static because of unit testing.
    const ResourceMap resources = TranslationResources::get();
    const ResourceMap::const_iterator itBegin = resources.begin();

    LocaleDescriptor savedKey = loadLocaleSetting();
    auto itKey = resources.find(savedKey);
    if (itKey != resources.end()) {
        setIndex(std::distance(itBegin, itKey));
        return index_;
    }

    // Alternatively set to a locale for a different territory.
    auto sameLanguage = [savedKey](const ResourcePair &r) -> bool {
        return r.first.language == savedKey.language;
    };
    itKey = std::ranges::find_if(resources, sameLanguage);
    if (itKey != resources.end()) {
        setIndex(std::distance(itBegin, itKey));
        return index_;
    }

    // If no alternative was found, use the first language in the list.
    setIndex(0);
    return index_;
}

bool Tts::LanguageSettings::isInAutoMode()
{
    const auto resourcesSize = TranslationResources::get().size();

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
    auto resources = TranslationResources::get();

    if (index_ < 0 || index_ >= resources.size())
        return autoLocale();
    // When in auto mode, the list can still get shown in the UI, so the index
    // and the corresponding LocaleDescriptor are still needed.

    ResourceMap::iterator it = resources.begin();
    std::advance(it, index_);

    return it->first;
}
