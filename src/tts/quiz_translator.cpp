#include "quiz_translator.hpp"
#include "tts_settings.hpp"
#include "locale_descriptor.hpp"
#include "auto_locale.hpp"
#include <QFile>
#include <QDirIterator>

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
    // Update translation.
    // The class outlives QuizView being on top of the stack, so the locale
    // can be updated in the settings and would need to be applied when
    // returning to the view.
    if (!load())
        throw std::runtime_error("translation could not be loaded");

    return QTranslator::translate(context, sourceText, disambiguation, n);
}

// TODO this can be a namespace function?
// name it getLocaleDescriptor otherwise?
// or should this be a method in Settings?
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

bool Tts::QuizTranslator::load()
{
    // Get updated locale.
    Tts::LocaleDescriptor ld = loadLocale();
    auto l = QLocale(ld.language, ld.territory);
    QString updatedLanguageCode = l.languageToCode(ld.language);
    // Update translation, if the locale changed.
    if (QTranslator::language() == updatedLanguageCode)
        return true;

    QString resourcePath = QuizTranslator::resources()[ld];
    return QTranslator::load(resourcePath);

    // TODO would it be possible to have separate qm files for tts?
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

Tts::ResourceMap &Tts::QuizTranslator::resources()
{
    static ResourceMap resources;

    if (resources.size() > 0)
        return resources;

    // ":" is the base path for Qt Resource files.
    QDirIterator it(":", { "*.qm" }, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString dir = it.next();
        auto descriptor = LocaleDescriptor::fromResourcePath(dir);

        resources.insert({ descriptor, dir });
    }

    return resources;
}
