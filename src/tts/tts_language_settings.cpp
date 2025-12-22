#include "tts_language_settings.hpp"
#include "translation_resources.hpp"

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
    saveLocaleSetting(Tts::TranslationResources::locale(index_));
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
