#ifndef OTTQ_20250829_1805_INCLUDE
#define OTTQ_20250829_1805_INCLUDE

#include <QLocale>

namespace Tts {

struct LocaleDescriptor
{
    LocaleDescriptor(const QLocale::Language l, const QLocale::Territory t)
        : language(l), territory(t)
    {
    }

    LocaleDescriptor(const QLocale l)
        : language(l.language()), territory(l.territory())
    {
    }

    bool operator==(const LocaleDescriptor &ld) const
    {
        return language == ld.language && territory == ld.territory;
    }

    QLocale::Language language;
    QLocale::Territory territory;
};

} // namespace Tts

#endif // OTTQ_20250829_1805_INCLUDE
