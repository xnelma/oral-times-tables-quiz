#ifndef OTTQ_20260106_2042_INCLUDE
#define OTTQ_20260106_2042_INCLUDE

#include "abstract_translator.hpp"
#include <QTranslator>

namespace Tts {

class Translator : public AbstractTranslator
{
public:
    Translator(QObject *parent = nullptr);

    QString filePath() override;
    QLocale locale() override;
    QString translate(const char *context, const char *sourceText,
                      const char *disambiguation = nullptr,
                      int n = -1) override;
    bool load(const QString &filename) override;

private:
    QTranslator translator_;
};

} // namespace Tts

#endif // OTTQ_20260106_2042_INCLUDE
