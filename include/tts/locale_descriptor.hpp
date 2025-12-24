#ifndef OTTQ_20250829_1805_INCLUDE
#define OTTQ_20250829_1805_INCLUDE

#include <QLocale>
#include <ostream>

namespace Tts {

struct LocaleDescriptor
{
    explicit LocaleDescriptor();
    LocaleDescriptor(LocaleDescriptor const &other) = default;
    LocaleDescriptor(LocaleDescriptor &&) noexcept = default;
    explicit LocaleDescriptor(const QLocale::Language &l,
                              const QLocale::Territory &t);
    explicit LocaleDescriptor(const QLocale &l);
    virtual ~LocaleDescriptor() = default;

    static Tts::LocaleDescriptor fromFileName(const QString &qmFileName);
    static Tts::LocaleDescriptor fromResourcePath(const QString &qmPath);

    LocaleDescriptor &operator=(LocaleDescriptor const &) = default;
    LocaleDescriptor &operator=(LocaleDescriptor &&) = default;

    bool operator==(const LocaleDescriptor &ld) const;
    bool operator<(const LocaleDescriptor &ld) const;

    QLocale::Language language;
    QLocale::Territory territory;
};

} // namespace Tts

std::ostream &operator<<(std::ostream &os, const Tts::LocaleDescriptor &ld);

#endif // OTTQ_20250829_1805_INCLUDE
