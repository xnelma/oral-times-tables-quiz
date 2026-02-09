#ifndef OTTQ_20250829_1805_INCLUDE
#define OTTQ_20250829_1805_INCLUDE

#include <QLocale>
#include <ostream>
#include <format>

namespace Tts {

struct LocaleDescriptor
{
    LocaleDescriptor();
    LocaleDescriptor(LocaleDescriptor const &other) = default;
    LocaleDescriptor(LocaleDescriptor &&) noexcept = default;
    explicit LocaleDescriptor(const QLocale::Language &l,
                              const QLocale::Territory &t);
    explicit LocaleDescriptor(const QLocale &l);
    virtual ~LocaleDescriptor() = default;

    static Tts::LocaleDescriptor fromFileName(const std::string &qmFileName);
    static Tts::LocaleDescriptor fromResourcePath(const QString &qmPath);

    LocaleDescriptor &operator=(LocaleDescriptor const &) = default;
    LocaleDescriptor &operator=(LocaleDescriptor &&) = default;

    bool operator==(const LocaleDescriptor &ld) const;
    bool operator<(const LocaleDescriptor &ld) const;

    virtual LocaleDescriptor resourceKey() const { return *this; }

    QLocale::Language language;
    QLocale::Territory territory;
};

std::ostream &operator<<(std::ostream &os, const Tts::LocaleDescriptor &ld);

} // namespace Tts

template <class CharT>
struct std::formatter<Tts::LocaleDescriptor, CharT>
    : std::formatter<std::string, CharT>
{
    template <typename FormatContext>
    auto format(Tts::LocaleDescriptor &ld, FormatContext &fc) const
    {
        auto languageStr = QLocale::languageToString(ld.language);
        auto territoryStr = QLocale::territoryToString(ld.territory);

        return std::formatter<string>::format(
            std::format("({}, {})",
                        languageStr.toUtf8().data(),
                        territoryStr.toUtf8().data()),
            fc);
    }
};

#endif // OTTQ_20250829_1805_INCLUDE
