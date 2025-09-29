#ifndef OTTQ_20250829_1810_INCLUDE
#define OTTQ_20250829_1810_INCLUDE

#include "tts/quiz_translator.hpp"
#include "timestables/quiz.hpp"
#include <QObject>
#include <qqml.h>
#include <QLocale>
#include <QString>

class QuizBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double voiceRate READ voiceRate NOTIFY voiceRateChanged FINAL)
    Q_PROPERTY(QString question READ question NOTIFY questionChanged FINAL)
    // clang-format off
    Q_PROPERTY(QString localeName
               READ localeName
               NOTIFY localeNameChanged
               FINAL)
    Q_PROPERTY(bool isAvailable
               READ isAvailable
               WRITE setAvailability
               NOTIFY availabilityChanged
               FINAL)
    Q_PROPERTY(int numQuestionsRemaining
               READ numQuestionsRemaining
               NOTIFY numQuestionsRemainingChanged
               FINAL)
    Q_PROPERTY(QString state // TODO enum?
               READ state
               WRITE setState
               NOTIFY stateChanged
               FINAL)
    // clang-format on
    QML_ELEMENT

public:
    explicit QuizBackend(QObject *parent = nullptr);

    QString localeName();
    double voiceRate();
    QString question();
    bool isAvailable();
    int numQuestionsRemaining();
    QString state();

    void setAvailability(const bool &isAvailable);
    void setState(const QString &state);

    Q_INVOKABLE bool setupQuiz();
    Q_INVOKABLE void startQuiz();
    Q_INVOKABLE void check(const QString input);

signals:
    void localeNameChanged();
    void voiceRateChanged();
    void availabilityChanged();
    void numQuestionsRemainingChanged();
    void questionChanged();
    void quizCompleted();
    void stateChanged();

private:
    void nextQuestion();

    Tts::QuizTranslator translator_;
    bool isAvailable_;
    TimesTables::Quiz quiz_;
    QString questionBase_;
    QString state_;
};

#endif // OTTQ_20250829_1810_INCLUDE
