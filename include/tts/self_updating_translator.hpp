#ifndef OTTQ_20260112_0952_INCLUDE
#define OTTQ_20260112_0952_INCLUDE

#include "abstract_translator.hpp"
#include "abstract_tts_settings.hpp"
#include "tts_settings.hpp"
#include "translator.hpp"

namespace Tts {

template <typename T>
concept ExtendsTranslator = std::is_base_of_v<Tts::AbstractTranslator, T>;

#ifndef EXTENDS_RESOURCES
#  define EXTENDS_RESOURCES
template <typename TR>
concept ExtendsResources = std::is_base_of_v<Tts::TranslationResources, TR>;
// C++20
#endif // EXTENDS_RESOURCES

template <ExtendsTranslator TTranslator = Tts::Translator,
          ExtendsResources TTranslationResources = Tts::TranslationResources>
class SelfUpdatingTranslator : public TTranslator
{
private:
    std::shared_ptr<Tts::AbstractSettings> settings_;

    bool load(const QString &filename) override
    {
        return TTranslator::load(filename);
    }

    void updateLocale()
    {
        auto localeDescriptor = TTranslator::localeDescriptor();
        auto settingsLocaleDescriptor =
            settings_->resolvedLocale().resourceKey();
        if (settingsLocaleDescriptor == localeDescriptor)
            return;
        localeDescriptor = std::move(settingsLocaleDescriptor);

        if (TTranslationResources::get().empty())
            throw std::invalid_argument("Translation resources are empty.");

        if (!TTranslationResources::get().contains(localeDescriptor)) {
            std::stringstream ss;
            ss << localeDescriptor;
            throw std::invalid_argument(
                std::format("No matching key in translation resources for "
                            "locale descriptor {}.",
                            ss.str()));
        }

        QString resourcePath =
            TTranslationResources::get().at(localeDescriptor);
        bool ok = TTranslator::load(resourcePath);

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
        : TTranslator(parent), settings_(settings)
    {
    }

    QString translate(const char *context, const char *sourceText,
                      const char *disambiguation = nullptr, int n = -1)
    {
        updateLocale();
        return TTranslator::translate(context, sourceText, disambiguation, n);
    }
};

} // namespace Tts

#endif // OTTQ_20260112_0952_INCLUDE
