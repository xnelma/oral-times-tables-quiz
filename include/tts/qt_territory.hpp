#if !defined OTTQ_20260413_1548_INCLUDE && defined QT_TRANSLATOR
#  define OTTQ_20260413_1548_INCLUDE

#  include <QLocale>

namespace Tts {
namespace Territory {

enum Code {
    ANY = QLocale::AnyTerritory,
    DE = QLocale::Germany,
    US = QLocale::UnitedStates,
    UK = QLocale::UnitedKingdom,
    FR = QLocale::France,
    IT = QLocale::Italy
};

static Code fromString(const std::string &territoryCode)
{
    return static_cast<Code>(
        QLocale::codeToTerritory(QString::fromStdString(territoryCode)));
}

static std::string toString(const Code &territoryCode)
{
    return QLocale::territoryToString(
               static_cast<QLocale::Territory>(territoryCode))
        .toStdString();
}

} // namespace Territory
} // namespace Tts

#endif // OTTQ_20260413_1548_INCLUDE