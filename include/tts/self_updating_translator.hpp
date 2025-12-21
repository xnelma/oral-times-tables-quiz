#ifndef OTTQ_20250829_1807_INCLUDE
#define OTTQ_20250829_1807_INCLUDE

#include "tts_settings.hpp"
#include "locale_descriptor.hpp"
#include <QLocale>
#include <QString>
#include <QTranslator>
#include <unordered_map>

template <>
struct std::hash<Tts::LocaleDescriptor>
{
    std::size_t operator()(const Tts::LocaleDescriptor &ld) const
    {
        return std::hash<int>()(ld.language)
            ^ std::hash<int>()(ld.territory << 1);
    }
};

// TODO should even for subdirectories the top namespace be OTTQ?

namespace Tts {

typedef std::unordered_map<Tts::LocaleDescriptor, QString> ResourceMap;
typedef std::pair<Tts::LocaleDescriptor, QString> ResourcePair;

class SelfUpdatingTranslator : public QTranslator, private Settings
{
public:
    explicit SelfUpdatingTranslator(QObject *parent = nullptr);

    Tts::LocaleDescriptor localeDescriptor();
    QLocale locale();
    QString translate(const char *contex, const char *sourceText,
                      const char *disambiguation = nullptr, int n = -1);

    static ResourceMap &resources();

private:
    LocaleDescriptor loadLocale();

    bool load();
    // hide load(.), because a manually loaded translation would be overriden.
    bool load(const QString &filename, const QString &directory = QString(),
              const QString &searchDelimiters = QString(),
              const QString &suffix = QString());
    bool load(const QLocale &locale, const QString &filename,
              const QString &prefix = QString(),
              const QString &directory = QString(),
              const QString &suffix = QString());
    bool load(const uchar *data, int len, const QString &directory = QString());
};

} // namespace Tts

#endif // OTTQ_20250829_1807_INCLUDE
