#ifndef OTTQ_20250829_1807_INCLUDE
#define OTTQ_20250829_1807_INCLUDE

#include "abstract_tts_settings.hpp"
#include "tts_settings.hpp"
#include "locale_descriptor.hpp"
#include <QLocale>
#include <QString>
#include <QTranslator>

namespace Tts {

class SelfUpdatingTranslator : public QTranslator
{
public:
    explicit SelfUpdatingTranslator(
        QObject *parent = nullptr,
        std::shared_ptr<Tts::AbstractSettings> settings =
            std::make_shared<Tts::Settings>());

    Tts::LocaleDescriptor localeDescriptor();
    QLocale locale();
    QString translate(const char *contex, const char *sourceText,
                      const char *disambiguation = nullptr, int n = -1);

private:
    std::shared_ptr<Tts::AbstractSettings> settings_;

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
