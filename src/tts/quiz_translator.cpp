#include "quiz_translator.hpp"
#include "tts_settings.hpp"
#include "locale_descriptor.hpp"
#include "auto_locale.hpp"
#include "translator_resources.hpp"

// TODO maybe this doesn't need to be a class?

Tts::QuizTranslator::QuizTranslator() : localeDescriptor_(loadLocale()) { }

QLocale Tts::QuizTranslator::locale()
{
    return QLocale(localeDescriptor_.language, localeDescriptor_.territory);
}

// TODO maybe this can also partially be a namespace function?
void Tts::QuizTranslator::translate(QString &question)
{
    // Update locale.
    // The class outlives QuizView, so a change in the settings needs to be
    // handled here.
    // TODO This might change in the future.
    localeDescriptor_ = loadLocale();
    // Update translation, if the locale changed.
    auto l = QLocale(localeDescriptor_.language, localeDescriptor_.territory);
    QString languageCode = l.languageToCode(localeDescriptor_.language);
    if (translator_.language() != languageCode)
        loadTranslation();

    question = translator_.translate("QuizView", question.toLocal8Bit().data());
}

// TODO this can be a namespace function?
auto Tts::QuizTranslator::loadLocale() -> LocaleDescriptor
{
    bool useAutoLocale = loadAutoLocaleSetting();
    if (useAutoLocale)
        return autoLocale();

    LocaleDescriptor ld = loadLocaleSetting();
    if (ld.language <= QLocale::C) {
        return autoLocale();
    }
    // If the territory is QLocale::AnyTerritory, that's the same as the
    // default argument for QLocale, so it doesn't need to be checked.

    return ld;
}

void Tts::QuizTranslator::loadTranslation()
{
    QString resourcePath = Translator::resources()[localeDescriptor_];
    if (!translator_.load(resourcePath))
        throw std::runtime_error("translation could not be loaded");

    // TODO would it be possible to have separate qm files for tts?
}
