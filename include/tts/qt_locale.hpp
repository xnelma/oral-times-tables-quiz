#if !defined OTTQ_20260301_1821_INCLUDE // TODO && defined QT_TRANSLATOR
#  define OTTQ_20260301_1821_INCLUDE

#  include <QLocale>
#  include <string>

namespace Tts {

typedef QLocale::Language Language;
typedef QLocale::Territory Territory;

static const Language anyLanguage = QLocale::AnyLanguage;
static const Language c = QLocale::C;
static const Territory anyTerritory = QLocale::AnyTerritory;

struct Locale
{
public:
    Locale()
    {
        // Init with default constructor for QLocale instead of
        // QLocale::system() to allow setting a different 'system' locale by
        // setting a default locale, for example for unit testing.
        QLocale l;
        language_ = l.language();
        territory_ = l.territory();
    }

    Language language() const { return language_; }
    Territory territory() const { return territory_; }

    // TODO move to free function?
    static Language language(const std::string &languageCode)
    {
        return QLocale::codeToLanguage(QString::fromStdString(languageCode));
    }

    static Territory territory(const std::string &territoryCode)
    {
        return QLocale::codeToTerritory(QString::fromStdString(territoryCode));
    }

private:
    Language language_;
    Territory territory_;
};

} // namespace Tts

#endif // OTTQ_20260301_1821_INCLUDE
