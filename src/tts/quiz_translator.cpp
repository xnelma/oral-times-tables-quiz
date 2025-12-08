#include "quiz_translator.hpp"
#include "tts_settings.hpp"
#include "locale_descriptor.hpp"
#include "auto_locale.hpp"
#include "translator_resources.hpp"

Tts::QuizTranslator::QuizTranslator(QObject *parent) : QTranslator(parent) { }

QLocale Tts::QuizTranslator::locale()
{
    auto ld = Tts::LocaleDescriptor::fromResourcePath(QTranslator::filePath());
    return QLocale(ld.language, ld.territory);
}

QString Tts::QuizTranslator::translate(const char *context,
                                       const char *sourceText,
                                       const char *disambiguation, int n)
{
    // Update locale.
    // The class outlives QuizView, so a change in the settings needs to be
    // handled here.
    // TODO This might change in the future.
    Tts::LocaleDescriptor ld = loadLocale();
    // Update translation, if the locale changed.
    auto l = QLocale(ld.language, ld.territory);
    QString updatedLanguageCode = l.languageToCode(ld.language);
    if (QTranslator::language() != updatedLanguageCode) {
        QString resourcePath = Translator::resources()[ld];
        if (!QTranslator::load(resourcePath))
            throw std::runtime_error("translation could not be loaded");

        // TODO would it be possible to have separate qm files for tts?
    }

    return QTranslator::translate(context, sourceText, disambiguation, n);
}

// TODO this can be a namespace function?
// or maybe it can be moved to load(.)?
// name it setLocale otherwise?
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

bool Tts::QuizTranslator::load(const QString &filename,
                               const QString &directory,
                               const QString &searchDelimiters,
                               const QString &suffix)
{
    return QTranslator::load(filename, directory, searchDelimiters, suffix);
}

bool Tts::QuizTranslator::load(const QLocale &locale, const QString &filename,
                               const QString &prefix, const QString &directory,
                               const QString &suffix)
{
    return QTranslator::load(locale, filename, prefix, directory, suffix);
}

bool Tts::QuizTranslator::load(const uchar *data, int len,
                               const QString &directory)
{
    return QTranslator::load(data, len, directory);
}
