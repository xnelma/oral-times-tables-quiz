#if !defined OTTQ_20260301_1821_INCLUDE && defined QT_TRANSLATOR
#  define OTTQ_20260301_1821_INCLUDE

#  include <QLocale>
#  include <string>

namespace Tts {

typedef QLocale BaseType;

enum Language {
    any = QLocale::AnyLanguage,
    c = QLocale::C,
    de = QLocale::German,
    en = QLocale::English,
    fr = QLocale::French,
    it = QLocale::Italian
};

enum Territory {
    ANY = QLocale::AnyTerritory,
    DE = QLocale::Germany,
    US = QLocale::UnitedStates,
    UK = QLocale::UnitedKingdom,
    FR = QLocale::France,
    IT = QLocale::Italy
};

struct Locale
{
public:
    Locale() { }

    explicit Locale(const Tts::Language &l, const Tts::Territory &t)
        : qtLocale_(QLocale(static_cast<QLocale::Language>(l),
                            static_cast<QLocale::Territory>(t)))
    {
    }

    Language language() const
    {
        return static_cast<Tts::Language>(qtLocale_.language());
    }

    Territory territory() const
    {
        return static_cast<Tts::Territory>(qtLocale_.territory());
    }

    // TODO move to free function?
    static Language language(const std::string &languageCode)
    {
        return static_cast<Language>(
            QLocale::codeToLanguage(QString::fromStdString(languageCode)));
    }

    static Territory territory(const std::string &territoryCode)
    {
        return static_cast<Territory>(
            QLocale::codeToTerritory(QString::fromStdString(territoryCode)));
    }

    static std::string languageName(const Tts::Language &l)
    {
        // Asserting the type of the parameter should not be necessary, because
        // a wrong typedef should be detected at compile time.
        return QLocale::languageToString(static_cast<QLocale::Language>(l))
            .toUtf8()
            .data();
    }

    static std::string territoryName(const Tts::Territory &t)
    {
        return QLocale::territoryToString(static_cast<QLocale::Territory>(t))
            .toUtf8()
            .data();
    }

    std::string name() { return qtLocale_.name().toStdString(); }

    static void setDefault(const Tts::Language &l, const Tts::Territory &t)
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
