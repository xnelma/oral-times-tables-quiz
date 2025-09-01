#ifndef QUIZ_BACKEND_HPP
#define QUIZ_BACKEND_HPP

#include "quiz_translator.hpp"
#include <QObject>
#include <qqml.h>
#include <QLocale>
#include <QString>

class QuizBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString localeName READ localeName NOTIFY localeNameChanged)
    Q_PROPERTY(double voiceRate READ voiceRate NOTIFY voiceRateChanged)
    // clang-format off
    Q_PROPERTY(bool isAvailable
               READ isAvailable
               WRITE setAvailability
               NOTIFY availabilityChanged)
    Q_PROPERTY(int numQuestionsRemaining
               READ numQuestionsRemaining
               NOTIFY numQuestionsRemainingChanged)
    // clang-format on
    QML_ELEMENT

public:
    explicit QuizBackend(QObject *parent = nullptr);

    QString localeName();
    double voiceRate();
    bool isAvailable();
    void setAvailability(const bool &isAvailable);
    int numQuestionsRemaining();

    Q_INVOKABLE QString getQuestion();
    Q_INVOKABLE void startQuiz(const QList<int> tables, const int minFactor,
                               const int maxFactor);

signals:
    void localeNameChanged();
    void voiceRateChanged();
    void availabilityChanged();
    void numQuestionsRemainingChanged();

private:
    Tts::QuizTranslator translator_;
    bool isAvailable_;
    const QString question_;
};

#endif // QUIZ_BACKEND_HPP
