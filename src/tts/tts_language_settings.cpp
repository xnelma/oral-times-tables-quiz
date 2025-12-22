#include "tts_language_settings.hpp"
#include "auto_locale.hpp"
#include "translation_resources.hpp"
#include <QDir>

Tts::LanguageSettings::LanguageSettings()
    : isInAutoMode_(loadAutoLocaleSetting()), index_(-1)
{
}

bool Tts::LanguageSettings::isInAutoMode()
{
    // TODO set to auto mode for invalid index
    return isInAutoMode_;
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
