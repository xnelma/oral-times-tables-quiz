#include "self_updating_translator.hpp"
#include "tts_settings.hpp"
#include "locale_descriptor.hpp"
#include "auto_locale.hpp"
#include "translation_resources.hpp"
#include <QFile>
#include <QDirIterator>
#include <string>
#include <sstream>

Tts::SelfUpdatingTranslator::SelfUpdatingTranslator(
    QObject *parent, std::shared_ptr<Tts::AbstractSettings> settings)
    : translator_(QTranslator(parent)), settings_(settings)
{
}

auto Tts::SelfUpdatingTranslator::localeDescriptor() -> LocaleDescriptor
{
    return Tts::LocaleDescriptor::fromResourcePath(translator_.filePath());
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
    bool ok = false;
    std::string msg = "";
    try {
        ok = load();
    } catch (const std::invalid_argument &e) {
        msg = e.what();
    }

    if (!ok) {
        throw std::runtime_error(
            "translation could not be loaded" + msg != "" ? msg : "");
    }

    return translator_.translate(context, sourceText, disambiguation, n);
}

bool Tts::SelfUpdatingTranslator::load()
{
    // Update translation, if the locale changed.
    Tts::LocaleDescriptor updatedLocaleKey = settings_->locale().resourceKey();
    if (localeDescriptor() == updatedLocaleKey)
        return true;

    std::stringstream ss;
    ss << updatedLocaleKey;
    if (!TranslationResources::get().contains(updatedLocaleKey))
        throw std::invalid_argument("Invalid locale descriptor " + ss.str());

    QString resourcePath = TranslationResources::get().at(updatedLocaleKey);
    if (!QFile(resourcePath).exists())
        throw std::invalid_argument("Invalid resource path \""
                                    + resourcePath.toStdString() + "\"");

    return translator_.load(resourcePath);

    // TODO would it be possible to have separate qm files for tts?
}
