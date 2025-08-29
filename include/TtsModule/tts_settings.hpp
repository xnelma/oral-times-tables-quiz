#ifndef TTS_SETTINGS_HPP
#define TTS_SETTINGS_HPP

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
    void saveLocaleSetting(const LocaleDescriptor &ld);
    void saveAutoLocaleSetting(const bool useAutoLocale);

private:
    const QString languageKey_;
    const QString territoryKey_;
    const QString autoLocaleKey_;

    QSettings settings_;
};

} // namespace Tts

#endif // TTS_SETTINGS_HPP
