#ifndef QUIZ_TRANSLATOR_HPP
#define QUIZ_TRANSLATOR_HPP

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
    bool isAvailable();

private:
    QLocale loadLocale();
    void loadTranslation();

    QLocale locale_;
    QTranslator translator_;
    bool isAvailable_;
};

} // namespace Tts

#endif // QUIZ_TRANSLATOR_HPP
