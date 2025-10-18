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
    // clang-format off
    Q_PROPERTY(QString localeName
               READ localeName
               NOTIFY localeNameChanged
               FINAL)
    Q_PROPERTY(int numQuestionsRemaining
               READ numQuestionsRemaining
               NOTIFY numQuestionsRemainingChanged
               FINAL)
    Q_PROPERTY(QString state // TODO enum?
               READ state
               WRITE setState
               // TODO maybe instead of the one-line assignProperty
               // set the states in connect s.t. I don't need to expose the
               // WRITE function to QML?
               NOTIFY stateChanged
               FINAL)
    // clang-format on
    QML_ELEMENT

public:
    explicit QuizBackend(QObject *parent = nullptr);

    QString state();
    QString localeName();
    int numQuestionsRemaining();

    void setState(const QString &s);

    Q_INVOKABLE void check(const QString input);
    Q_INVOKABLE void askAgain();

signals:
    void localeNameChanged();
    void numQuestionsRemainingChanged();
    void questionChanged();
    void stateChanged();
    void showLocaleError();
    void completed();

    void error();
    void setupStepDone();
    void setupDoneAndTtsReady();
    void setupDoneAndTtsError();

private slots:
    void setupQuiz();
    void setupTranslation();

private:
    void setupStateMachine();
    void setupTts();
    void synthesizeFirstQuestion();
    double voiceRate();
    QString question();
    void nextQuestion();

    QString state_;
    Tts::QuizTranslator translator_;
    TimesTables::Quiz quiz_;
    QString questionBase_;
};

#endif // OTTQ_20250829_1810_INCLUDE
