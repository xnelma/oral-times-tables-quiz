#ifndef OTTQ_20250829_1807_INCLUDE
#define OTTQ_20250829_1807_INCLUDE

#include "tts_settings.hpp"
#include <QLocale>
#include <QString>
#include <QTranslator>

namespace Tts {

class QuizTranslator : public Settings
{
public:
    QuizTranslator();

    QLocale locale();
    void translate(QString &question);

private:
    LocaleDescriptor loadLocale();
    void loadTranslation();

    LocaleDescriptor localeDescriptor_;
    QTranslator translator_;
};

} // namespace Tts

#endif // OTTQ_20250829_1807_INCLUDE
