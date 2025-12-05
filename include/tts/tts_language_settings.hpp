#ifndef OTTQ_20250829_1808_INCLUDE
#define OTTQ_20250829_1808_INCLUDE

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
    void loadIndex();
    LocaleDescriptor indexDescriptor();

    bool isInAutoMode_;
    QStringList languages_;
    int index_;
};

} // namespace Tts

#endif // OTTQ_20250829_1808_INCLUDE
