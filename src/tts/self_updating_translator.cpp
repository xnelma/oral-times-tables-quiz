#include "self_updating_translator.hpp"
#include "tts_settings.hpp"
#include "locale_descriptor.hpp"
#include "auto_locale.hpp"
#include <QFile>
#include <QDirIterator>

Tts::SelfUpdatingTranslator::SelfUpdatingTranslator(QObject *parent)
    : QTranslator(parent)
{
}

QLocale Tts::SelfUpdatingTranslator::locale()
{
    auto ld = Tts::LocaleDescriptor::fromResourcePath(QTranslator::filePath());
    return QLocale(ld.language, ld.territory);
}

QString Tts::SelfUpdatingTranslator::translate(const char *context,
                                               const char *sourceText,
                                               const char *disambiguation,
                                               int n)
{
    // Update translation.
    if (!load())
        throw std::runtime_error("translation could not be loaded");

    return QTranslator::translate(context, sourceText, disambiguation, n);
}

// TODO this can be a namespace function?
// name it getLocaleDescriptor otherwise?
// or should this be a method in Settings?
auto Tts::SelfUpdatingTranslator::loadLocale() -> LocaleDescriptor
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

bool Tts::SelfUpdatingTranslator::load()
{
    // Update translation, if the locale changed.
    Tts::LocaleDescriptor updatedLocale = loadLocale();
    if (language() == QLocale::languageToCode(updatedLocale.language))
        return true;

    QString resourcePath = resources()[updatedLocale];
    return load(resourcePath);

    // TODO would it be possible to have separate qm files for tts?
}

bool Tts::SelfUpdatingTranslator::load(const QString &filename,
                                       const QString &directory,
                                       const QString &searchDelimiters,
                                       const QString &suffix)
{
    return QTranslator::load(filename, directory, searchDelimiters, suffix);
}

bool Tts::SelfUpdatingTranslator::load(const QLocale &locale,
                                       const QString &filename,
                                       const QString &prefix,
                                       const QString &directory,
                                       const QString &suffix)
{
    return QTranslator::load(locale, filename, prefix, directory, suffix);
}

bool Tts::SelfUpdatingTranslator::load(const uchar *data, int len,
                                       const QString &directory)
{
    return QTranslator::load(data, len, directory);
}

Tts::ResourceMap &Tts::SelfUpdatingTranslator::resources()
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
