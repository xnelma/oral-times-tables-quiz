#ifndef OTTQ_20251222_1929_INCLUDE
#define OTTQ_20251222_1929_INCLUDE

#include "locale_descriptor.hpp"
#include "auto_locale.hpp"
#include "translation_resources.hpp"

namespace Tts {

class AbstractSettings
{
private:
    LocaleDescriptor locale_;

protected:
    virtual LocaleDescriptor &getAutoLocale() = 0;
    LocaleDescriptor &getLocale() { return locale_; }
    void setLocale(const Tts::LocaleDescriptor &locale) { locale_ = locale; }

public:
    AbstractSettings() { }
    AbstractSettings(AbstractSettings const &) = default;
    AbstractSettings(AbstractSettings &&) noexcept = default;
    virtual ~AbstractSettings() = default;

    AbstractSettings &operator=(AbstractSettings const &) = default;
    AbstractSettings &operator=(AbstractSettings &&) noexcept = default;

    LocaleDescriptor &locale()
    {
        locale_ = loadLocaleSetting();
        if (loadAutoLocaleSetting() || locale_.language <= QLocale::C) {
            return getAutoLocale();
        }

        return locale_;
    }

    virtual LocaleDescriptor loadLocaleSetting() = 0;
    virtual bool loadAutoLocaleSetting() = 0;
    virtual double loadVoiceRateSetting() = 0;

    virtual void saveLocaleSetting(const LocaleDescriptor &ld) = 0;
    virtual void saveAutoLocaleSetting(const bool useAutoLocale) = 0;
    virtual void saveVoiceRateSetting(const double rate) = 0;
};

} // namespace Tts

#endif // OTTQ_20251222_1929_INCLUDE
