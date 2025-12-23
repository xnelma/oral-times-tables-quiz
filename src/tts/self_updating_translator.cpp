#include "self_updating_translator.hpp"
#include "tts_settings.hpp"
#include "locale_descriptor.hpp"
#include "auto_locale.hpp"
#include "translation_resources.hpp"
#include <QFile>
#include <QDirIterator>

Tts::SelfUpdatingTranslator::SelfUpdatingTranslator(
    QObject *parent, std::shared_ptr<Tts::AbstractSettings> settings)
    : QTranslator(parent), settings_(settings)
{
}

auto Tts::SelfUpdatingTranslator::localeDescriptor() -> LocaleDescriptor
{
    return Tts::LocaleDescriptor::fromResourcePath(QTranslator::filePath());
}

QLocale Tts::SelfUpdatingTranslator::locale()
{
    auto ld = localeDescriptor();
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
    bool useAutoLocale = settings_->loadAutoLocaleSetting();
    if (useAutoLocale)
        return AutoLocale();

    LocaleDescriptor ld = settings_->loadLocaleSetting();
    if (ld.language <= QLocale::C) {
        return AutoLocale();
    }
    // If the territory is QLocale::AnyTerritory, that's the same as the
    // default argument for QLocale, so it doesn't need to be checked.

    return ld;
}

bool Tts::SelfUpdatingTranslator::load()
{
    // Update translation, if the locale changed.
    Tts::LocaleDescriptor updatedLocale = loadLocale();
    if (localeDescriptor() == updatedLocale)
        return true;

    QString resourcePath = TranslationResources::get()[updatedLocale];
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
