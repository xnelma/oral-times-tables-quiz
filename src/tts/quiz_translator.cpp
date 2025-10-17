#include "quiz_translator.hpp"
#include "tts_settings.hpp"
#include "locale_descriptor.hpp"
#include "auto_locale.hpp"

Tts::QuizTranslator::QuizTranslator() : isAvailable_(true)
{
    locale_ = loadLocale();
}

QLocale Tts::QuizTranslator::locale()
{
    return locale_;
}

void Tts::QuizTranslator::translate(QString &question)
{
    if (translator_.language() != locale_.languageToCode(locale_.language()))
        loadTranslation();

    question = translator_.translate("QuizView", question.toLocal8Bit().data());
}

bool Tts::QuizTranslator::isAvailable()
{
    return isAvailable_;
}

QLocale Tts::QuizTranslator::loadLocale()
{
    bool useAutoLocale = loadAutoLocaleSetting();
    if (useAutoLocale)
        return autoLocale();

    LocaleDescriptor ld = loadLocaleSetting();
    if (ld.language <= QLocale::C)
        return autoLocale();
    // If the territory is QLocale::AnyTerritory, that's the same as the
    // default argument for QLocale, so it doesn't need to be checked.

    return QLocale(ld.language, ld.territory);
}

void Tts::QuizTranslator::loadTranslation()
{
    if (!translator_.load(qmFilePath.arg(locale_.name())))
        throw std::runtime_error("translation could not be loaded");
}
