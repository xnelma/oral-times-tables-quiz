#ifndef OTTQ_20251222_1939_INCLUDE
#define OTTQ_20251222_1939_INCLUDE

#include "abstract_tts_settings.hpp"
#include "locale_descriptor.hpp"
#include "test_translation_resources.hpp"
#include "auto_locale.hpp"

class TestSettings : public Tts::AbstractSettings
{
private:
    Tts::LocaleDescriptor savedLocale_;
    bool savedUseAutoLocale_{ false };
    double savedVoiceRate_{ 0 };

    Tts::AutoLocale<TestTranslationResources> autoLocale_;

    Tts::LocaleDescriptor &autoLocale() override
    {
        autoLocale_ = Tts::AutoLocale<TestTranslationResources>();
        return autoLocale_;
    }

public:
    TestSettings() { }

    Tts::LocaleDescriptor loadLocaleSetting() override { return savedLocale_; }
    bool loadAutoLocaleSetting() override { return savedUseAutoLocale_; }
    double loadVoiceRateSetting() override { return savedVoiceRate_; }

    void saveLocaleSetting(const Tts::LocaleDescriptor &ld) override
    {
        savedLocale_ = std::move(ld);
    }
    void saveAutoLocaleSetting(const bool useAutoLocale) override
    {
        savedUseAutoLocale_ = useAutoLocale;
    }
    void saveVoiceRateSetting(const double voiceRate) override
    {
        savedVoiceRate_ = voiceRate;
    }
};

#endif // OTTQ_20251222_1939_INCLUDE
