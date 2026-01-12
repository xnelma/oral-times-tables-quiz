#ifndef OTTQ_20251222_1939_INCLUDE
#define OTTQ_20251222_1939_INCLUDE

#include "abstract_tts_settings.hpp"
#include "locale_descriptor.hpp"
#include "test_translation_resources.hpp"
#include "auto_locale.hpp"

class TestSettings : public Tts::AbstractSettings
{
private:
    bool useAutoLocale_{ false };
    double voiceRate_{ 0 };

    Tts::AutoLocale<TestTranslationResources> autoLocale_;

    Tts::LocaleDescriptor &autoLocale() override
    {
        autoLocale_ = Tts::AutoLocale<TestTranslationResources>();
        return autoLocale_;
    }

public:
    TestSettings() { }

    Tts::LocaleDescriptor loadLocaleSetting() override { return locale(); }
    bool loadAutoLocaleSetting() override { return useAutoLocale_; }
    double loadVoiceRateSetting() override { return voiceRate_; }

    void saveLocaleSetting(const Tts::LocaleDescriptor &ld) override
    {
        setLocale(ld);
    }
    void saveAutoLocaleSetting(const bool useAutoLocale) override
    {
        useAutoLocale_ = useAutoLocale;
    }
    void saveVoiceRateSetting(const double voiceRate) override
    {
        voiceRate_ = voiceRate;
    }
};

#endif // OTTQ_20251222_1939_INCLUDE
