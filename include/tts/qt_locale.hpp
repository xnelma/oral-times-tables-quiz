#if !defined OTTQ_20260301_1821_INCLUDE // TODO && defined QT_TRANSLATOR
#  define OTTQ_20260301_1821_INCLUDE

#  include <QLocale>

namespace Tts {

struct Locale
{
public:
    Locale()
    {
        QLocale l;
        language_ = l.language();
        territory_ = l.territory();
    }

    QLocale::Language language() const { return language_; }
    QLocale::Territory territory() const { return territory_; }

private:
    QLocale::Language language_;
    QLocale::Territory territory_;
};

} // namespace Tts

#endif // OTTQ_20260301_1821_INCLUDE
