#if !defined OTTQ_20260413_1545_INCLUDE && defined QT_TRANSLATOR
#  define OTTQ_20260413_1545_INCLUDE

#  include <QLocale>

namespace Tts {
namespace Language {

enum Code {
    any = QLocale::AnyLanguage,
    c = QLocale::C,
    de = QLocale::German,
    en = QLocale::English,
    fr = QLocale::French,
    it = QLocale::Italian
};

static Code fromString(const std::string &languageCode)
{
    return static_cast<Code>(
        QLocale::codeToLanguage(QString::fromStdString(languageCode)));
}

static std::string toString(const Code &languageCode)
{
    // Asserting the type of the parameter should not be necessary, because
    // a wrong typedef should be detected at compile time.
    return QLocale::languageToString(
               static_cast<QLocale::Language>(languageCode))
        .toStdString();
}

} // namespace Language
} // namespace Tts

#endif // OTTQ_20260413_1545_INCLUDE