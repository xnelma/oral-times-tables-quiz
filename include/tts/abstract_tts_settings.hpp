#ifndef OTTQ_20251222_1929_INCLUDE
#define OTTQ_20251222_1929_INCLUDE

#include "locale_descriptor.hpp"

namespace Tts {

class AbstractSettings
{
public:
    AbstractSettings() { }
    AbstractSettings(AbstractSettings const &) = default;
    AbstractSettings(AbstractSettings &&) noexcept = default;
    virtual ~AbstractSettings() = default;

    AbstractSettings &operator=(AbstractSettings const &) = default;
    AbstractSettings &operator=(AbstractSettings &&) noexcept = default;

    virtual LocaleDescriptor loadLocaleSetting() = 0;
    virtual bool loadAutoLocaleSetting() = 0;
    virtual double loadVoiceRateSetting() = 0;

    virtual void saveLocaleSetting(const LocaleDescriptor &ld) = 0;
    virtual void saveAutoLocaleSetting(const bool useAutoLocale) = 0;
    virtual void saveVoiceRateSetting(const double rate) = 0;
};

} // namespace Tts

#endif // OTTQ_20251222_1929_INCLUDE
