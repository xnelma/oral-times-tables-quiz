#ifndef OTTQ_20250829_1809_INCLUDE
#define OTTQ_20250829_1809_INCLUDE

#include "locale_descriptor.hpp"
#include <QString>
#include <QSettings>
#include <QLocale>

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
    QSettings settings_;
};

namespace SettingsKeys {

static const QString prefix = "Tts";
static const QString localePrefix = prefix + "Locale";

static const QString language = localePrefix + "/language";
static const QString territory = localePrefix + "/territory";
static const QString autoLocale = localePrefix + "/useAutoLocale";
static const QString voiceRate = prefix + "/voiceRate";

} // namespace SettingsKeys

namespace SettingsDefaults {

static const QLocale::Language language = QLocale::AnyLanguage;
static const QLocale::Territory territory = QLocale::AnyTerritory;
static const bool autoLocale = true;
static const double voiceRate = 0;

} // namespace SettingsDefaults

} // namespace Tts

#endif // OTTQ_20250829_1809_INCLUDE
