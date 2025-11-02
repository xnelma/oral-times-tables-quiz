#ifndef OTTQ_20250829_1809_INCLUDE
#define OTTQ_20250829_1809_INCLUDE

#include "locale_descriptor.hpp"
#include <QString>
#include <QSettings>

namespace Tts {

class Settings
{
public:
    Settings();

    LocaleDescriptor loadLocaleSetting();
    bool loadAutoLocaleSetting();
    double loadVoiceRateSetting();

    void saveLocaleSetting(const LocaleDescriptor &ld);
    void saveAutoLocaleSetting(const bool useAutoLocale);
    void saveVoiceRateSetting(const double rate);

private:
    const QString languageKey_;
    const QString territoryKey_;
    const QString autoLocaleKey_;
    const QString voiceRateKey_;

    QSettings settings_;
};

} // namespace Tts

#endif // OTTQ_20250829_1809_INCLUDE
