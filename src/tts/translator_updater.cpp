#include "translator_updater.hpp"
#include "locale_descriptor.hpp"
#include "translation_resources.hpp"
#include <QFile>
#include <sstream>

auto Tts::TranslatorUpdater::localeDescriptor(
    Tts::AbstractTranslator &translator) -> LocaleDescriptor
{
    return Tts::LocaleDescriptor::fromResourcePath(translator.filePath());
}

QLocale Tts::TranslatorUpdater::locale(Tts::AbstractTranslator &translator)
{
    auto ld = localeDescriptor(translator);
    return QLocale(ld.language, ld.territory);
}

bool Tts::TranslatorUpdater::updateLocaleKey(Tts::LocaleDescriptor &localeKey,
                                             Tts::AbstractSettings &settings)
{
    auto currentLocaleKey = settings.locale().resourceKey();
    if (currentLocaleKey == localeKey)
        return false;

    localeKey = currentLocaleKey;
    return true;
}

void Tts::TranslatorUpdater::update(
    Tts::AbstractTranslator &translator,
    const Tts::LocaleDescriptor &updatedLocaleKey)
{
    if (!TranslationResources::get().contains(updatedLocaleKey)) {
        std::stringstream ss;
        ss << updatedLocaleKey;
        throw std::invalid_argument(
            std::format("No matching key in translation resources for locale "
                        "descriptor {}.",
                        ss.str()));
    }

    QString resourcePath = TranslationResources::get().at(updatedLocaleKey);
    if (!QFile(resourcePath).exists())
        throw std::invalid_argument(
            std::format("Resource path \"{}\" does not exist.",
                        resourcePath.toStdString()));

    bool ok = translator.load(resourcePath);

    if (!ok)
        throw std::runtime_error("Translation could not be loaded.");

    // TODO would it be possible to have separate qm files for tts?
}
