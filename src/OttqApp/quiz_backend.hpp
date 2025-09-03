#ifndef QUIZ_BACKEND_HPP
#define QUIZ_BACKEND_HPP

#include "quiz_translator.hpp"
#include "quiz.hpp"
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
    int numQuestionsRemaining();

    void setAvailability(const bool &isAvailable);

    Q_INVOKABLE void startQuiz(const QList<int> tables, const int minFactor,
                               const int maxFactor);
    Q_INVOKABLE void check(const QString input);

signals:
    void localeNameChanged();
    void voiceRateChanged();
    void availabilityChanged();
    void numQuestionsRemainingChanged();
    void questionChanged(QString question);
    void quizCompleted();

private:
    void nextQuestion();

    Tts::QuizTranslator translator_;
    bool isAvailable_;
    TimesTables::Quiz quiz_;
    QString questionBase_;
};

#endif // QUIZ_BACKEND_HPP
