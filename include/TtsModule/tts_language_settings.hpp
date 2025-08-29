#ifndef TTS_LANGUAGE_SETTINGS_HPP
#define TTS_LANGUAGE_SETTINGS_HPP

#include "tts_settings.hpp"
#include "locale_descriptor.hpp"
#include <QLocale>
#include <QString>
#include <QStringList>
#include <map>
#include <vector>

namespace Tts {

class LanguageSettings : Settings
{
public:
    LanguageSettings();

    QStringList availableLanguages();
    int index();
    bool isInAutoMode();

    void setIndex(const int i);
    void setToAutoMode();
    void setToManualMode();

private:
    void loadMode();
    void loadLocaleDescriptors();
    void loadIndex();
    LocaleDescriptor indexDescriptor();

    bool isInAutoMode_;
    std::vector<LocaleDescriptor> localeDescriptors_;
    QStringList languages_;
    int index_;
};

} // namespace Tts

#endif // TTS_LANGUAGE_SETTINGS_HPP
