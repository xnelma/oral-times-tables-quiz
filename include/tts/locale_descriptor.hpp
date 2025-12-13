#ifndef OTTQ_20250829_1805_INCLUDE
#define OTTQ_20250829_1805_INCLUDE

#include <QLocale>
#include <ostream>

namespace Tts {

struct LocaleDescriptor
{
    explicit LocaleDescriptor();
    explicit LocaleDescriptor(const QLocale::Language &l,
                              const QLocale::Territory &t);
    explicit LocaleDescriptor(const QLocale &l);

    static Tts::LocaleDescriptor fromFileName(const QString &qmFileName);
    static Tts::LocaleDescriptor fromResourcePath(const QString &qmPath);

    bool operator==(const LocaleDescriptor &ld) const;
    bool operator<(const LocaleDescriptor &ld) const;

    QLocale::Language language;
    QLocale::Territory territory;
};

} // namespace Tts

std::ostream &operator<<(std::ostream &os, const Tts::LocaleDescriptor &ld);

#endif // OTTQ_20250829_1805_INCLUDE
