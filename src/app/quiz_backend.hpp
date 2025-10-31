#ifndef OTTQ_20250829_1810_INCLUDE
#define OTTQ_20250829_1810_INCLUDE

#include "quiz_state_machine.hpp"
#include "tts/quiz_translator.hpp"
#include "timestables/quiz.hpp"
#include <QObject>
#include <qqml.h>
#include <QLocale>
#include <QString>
#include <memory>

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
    Q_PROPERTY(QString state
               READ state
               NOTIFY stateChanged
               FINAL)
    // clang-format on
    QML_ELEMENT

public:
    explicit QuizBackend(QObject *parent = nullptr);

    QString state();
    QString localeName();
    int numQuestionsRemaining();

    Q_INVOKABLE void startStateMachine();
    Q_INVOKABLE void check(const QString input);
    Q_INVOKABLE void askAgain();
    Q_INVOKABLE void stopStateMachine();

signals:
    void localeNameChanged();
    void numQuestionsRemainingChanged();
    void questionChanged();
    void stateChanged();
    void showLocaleError();

private:
    void setupStateMachine();
    double voiceRate();
    QString question();
    void nextQuestion();

    std::unique_ptr<QuizStateMachine> machine_;
    Tts::QuizTranslator translator_;
    TimesTables::Quiz quiz_;
    QString questionBase_;
};

#endif // OTTQ_20250829_1810_INCLUDE
