#include "quiz_translator.hpp"
#include "tts_settings.hpp"
#include "locale_descriptor.hpp"
#include "auto_locale.hpp"
#include "translator_resources.hpp"

// TODO maybe this doesn't need to be a class?

Tts::QuizTranslator::QuizTranslator() : locale_(loadLocale()) { }

QLocale Tts::QuizTranslator::locale()
{
    return locale_;
    // TODO maybe I can save locale_ as a LocaleDescriptor and only create a
    // QLocale here.
}

void Tts::QuizTranslator::translate(QString &question)
{
    locale_ = loadLocale(); // update locale
    if (translator_.language() != locale_.languageToCode(locale_.language()))
        loadTranslation();

    question = translator_.translate("QuizView", question.toLocal8Bit().data());
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
    QString resourcePath = Translator::resources()[LocaleDescriptor(locale_)];
    if (!translator_.load(resourcePath))
        // why do I need to convert to locale descriptor here?
        throw std::runtime_error("translation could not be loaded");

    // TODO would it be possible to have separate qm files for tts?
}
