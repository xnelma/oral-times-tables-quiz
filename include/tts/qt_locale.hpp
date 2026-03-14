#if !defined OTTQ_20260301_1821_INCLUDE // TODO && defined QT_TRANSLATOR
#  define OTTQ_20260301_1821_INCLUDE

#  include <QLocale>
#  include <string>

namespace Tts {

typedef QLocale::Language Language;
typedef QLocale::Territory Territory;
typedef QLocale BaseType;

static const Language anyLanguage = QLocale::AnyLanguage;
static const Language c = QLocale::C;
static const Territory anyTerritory = QLocale::AnyTerritory;

struct Locale
{
public:
    Locale() { }

    explicit Locale(const Tts::Language &l, const Tts::Territory &t)
        : qtLocale_(QLocale(static_cast<QLocale::Language>(l),
                            static_cast<QLocale::Territory>(t)))
    {
    }

    Language language() const { return qtLocale_.language(); }
    Territory territory() const { return qtLocale_.territory(); }

    // TODO move to free function?
    static Language language(const std::string &languageCode)
    {
        return QLocale::codeToLanguage(QString::fromStdString(languageCode));
    }

    static Territory territory(const std::string &territoryCode)
    {
        return QLocale::codeToTerritory(QString::fromStdString(territoryCode));
    }

    static std::string languageName(const Tts::Language &l)
    {
        // Asserting the type of the parameter should not be necessary, because
        // a wrong typedef should be detected at compile time.
        return QLocale::languageToString(l).toUtf8().data();
    }

    static std::string nativeLanguageName(const Tts::Language &l,
                                          const Tts::Territory &t)
    {
        return QLocale(l, t).nativeLanguageName().toStdString();
    }

    static std::string territoryName(const Tts::Territory &t)
    {
        return QLocale::territoryToString(t).toUtf8().data();
    }

    std::string name() { return qtLocale_.name().toStdString(); }

    static void setDefault(const Tts::Language &l, const Tts::Territory &t)
    {
        QLocale::setDefault(QLocale(l, t));
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
