#if !defined OTTQ_20260301_1821_INCLUDE && defined QT_TRANSLATOR
#  define OTTQ_20260301_1821_INCLUDE

#  include "qt_language.hpp"
#  include "qt_territory.hpp"
#  include <QLocale>
#  include <string>

namespace Tts {

struct Locale
{
public:
    typedef QLocale BaseType;

    Locale() { }

    explicit Locale(const Language::Code &l, const Territory::Code &t)
        : qtLocale_(QLocale(static_cast<QLocale::Language>(l),
                            static_cast<QLocale::Territory>(t)))
    {
    }

    Language::Code language() const
    {
        return static_cast<Language::Code>(qtLocale_.language());
    }

    Territory::Code territory() const
    {
        return static_cast<Territory::Code>(qtLocale_.territory());
    }

    std::string name() { return qtLocale_.name().toStdString(); }

    static void setDefault(const Language::Code &l, const Territory::Code &t)
    {
        QLocale::setDefault(QLocale(static_cast<QLocale::Language>(l),
                                    static_cast<QLocale::Territory>(t)));
    }

    explicit operator BaseType() const { return qtLocale_; }

private:
    // Init with default constructor for QLocale instead of
    // QLocale::system() to allow setting a different 'system' locale by
    // setting a default locale, for example for unit testing.
    QLocale qtLocale_;
};

} // namespace Tts

#endif // OTTQ_20260301_1821_INCLUDE
