#ifndef OTTQ_20250829_1807_INCLUDE
#define OTTQ_20250829_1807_INCLUDE

#include "abstract_tts_settings.hpp"
#include "tts_settings.hpp"
#include "locale_descriptor.hpp"
#include <QLocale>
#include <QString>
#include <QTranslator>

namespace Tts {

class SelfUpdatingTranslator
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
    QTranslator translator_;

    bool load();
};

} // namespace Tts

#endif // OTTQ_20250829_1807_INCLUDE
