#ifndef OTTQ_20260106_2039_INCLUDE
#define OTTQ_20260106_2039_INCLUDE

#include <QString>
#include <QLocale>

namespace Tts {

class AbstractTranslator
{
public:
    AbstractTranslator() { }
    AbstractTranslator(AbstractTranslator const &) = default;
    AbstractTranslator(AbstractTranslator &&) noexcept = default;
    virtual ~AbstractTranslator() = default;

    AbstractTranslator &operator=(AbstractTranslator const &) = default;
    AbstractTranslator &operator=(AbstractTranslator &&) noexcept = default;

    virtual QString filePath() = 0;
    virtual QLocale locale() = 0;
    virtual QString translate(const char *context, const char *sourceText,
                              const char *disambiguation = nullptr,
                              int n = -1) = 0;
    virtual bool load(const QString &filename) = 0;
};

} // namespace Tts

#endif // OTTQ_20250106_2039_INCLUDE
