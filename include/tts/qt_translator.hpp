#if !defined OTTQ_20260106_2042_INCLUDE && defined QT_TRANSLATOR
#  define OTTQ_20260106_2042_INCLUDE

#  include "abstract_translator.hpp"
#  include <QTranslator>

namespace Tts {

class Translator : public AbstractTranslator
{
public:
    Translator(QObject *parent = nullptr);

    std::string filePath() override;
    Tts::LocaleDescriptor localeDescriptor() override;
    QLocale locale() override;
    std::string translate(const std::string &sourceText) override;
    bool load(const QString &filePath) override;

private:
    QTranslator translator_;
};

} // namespace Tts

#endif // OTTQ_20260106_2042_INCLUDE
