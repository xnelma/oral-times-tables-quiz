#ifndef OTTQ_20260112_0952_INCLUDE
#define OTTQ_20260112_0952_INCLUDE

#include "abstract_translator.hpp"
#include "abstract_tts_settings.hpp"
#include "tts_settings.hpp"
#include "translator.hpp"

namespace Tts {

template <typename T>
concept ExtendsTranslator = std::is_base_of_v<Tts::AbstractTranslator, T>;

template <ExtendsTranslator T = Tts::Translator>
class SelfUpdatingTranslator : public T
{
private:
    std::shared_ptr<Tts::AbstractSettings> settings_;

    bool load(const QString &filename) override { return T::load(filename); }

    void updateLocale()
    {
        auto localeDescriptor = T::localeDescriptor();
        auto settingsLocaleDescriptor = settings_->locale().resourceKey();
        if (settingsLocaleDescriptor == localeDescriptor)
            return;
        localeDescriptor = std::move(settingsLocaleDescriptor);

        if (!TranslationResources::get().contains(localeDescriptor)) {
            std::stringstream ss;
            ss << localeDescriptor;
            throw std::invalid_argument(
                std::format("No matching key in translation resources for "
                            "locale descriptor {}.",
                            ss.str()));
        }

        QString resourcePath = TranslationResources::get().at(localeDescriptor);
        if (!QFile(resourcePath).exists())
            throw std::invalid_argument(
                std::format("Resource path \"{}\" does not exist.",
                            resourcePath.toStdString()));

        bool ok = T::load(resourcePath);

        if (!ok)
            throw std::runtime_error("Translation could not be loaded.");

        // TODO would it be possible to have separate qm files for tts?
    }

public:
    explicit SelfUpdatingTranslator(
        std::shared_ptr<Tts::AbstractSettings> settings =
            std::make_shared<Tts::Settings>())
        : settings_(settings)
    {
    }

    explicit SelfUpdatingTranslator(
        QObject *parent,
        std::shared_ptr<Tts::AbstractSettings> settings =
            std::make_shared<Tts::Settings>())
        : T(parent), settings_(settings)
    {
    }

    QString translate(const char *context, const char *sourceText,
                      const char *disambiguation = nullptr, int n = -1)
    {
        updateLocale();
        return T::translate(context, sourceText, disambiguation, n);
    }
};

} // namespace Tts

#endif // OTTQ_20260112_0952_INCLUDE
