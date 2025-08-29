#ifndef LOCALE_DESCRIPTOR_HPP
#define LOCALE_DESCRIPTOR_HPP

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

#endif // LOCALE_DESCRIPTOR_HPP
