#ifndef OTTQ_20250829_1805_INCLUDE
#define OTTQ_20250829_1805_INCLUDE

#include "qt_locale.hpp"
#include <ostream>

namespace Tts {

struct LocaleDescriptor
{
    LocaleDescriptor();
    LocaleDescriptor(LocaleDescriptor const &other) = default;
    LocaleDescriptor(LocaleDescriptor &&) noexcept = default;
    explicit LocaleDescriptor(const Tts::Language &l, const Tts::Territory &t);
    explicit LocaleDescriptor(const Tts::Locale &l);
    virtual ~LocaleDescriptor() = default;

    static Tts::LocaleDescriptor fromFileName(const std::string &qmFileName);
    static Tts::LocaleDescriptor fromResourcePath(const std::string &qmPath);

    LocaleDescriptor &operator=(LocaleDescriptor const &) = default;
    LocaleDescriptor &operator=(LocaleDescriptor &&) = default;

    bool operator==(const LocaleDescriptor &ld) const;
    bool operator<(const LocaleDescriptor &ld) const;

    virtual LocaleDescriptor resourceKey() const { return *this; }

    // If the enum types would get abstracted by instead having a locale object
    // as class member of the descriptor, it would be against the point of
    // having the descriptor.
    Tts::Language language;
    Tts::Territory territory;
};

std::ostream &operator<<(std::ostream &os, const Tts::LocaleDescriptor &ld);

} // namespace Tts

#endif // OTTQ_20250829_1805_INCLUDE
