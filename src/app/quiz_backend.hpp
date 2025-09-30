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
    Q_PROPERTY(int numQuestionsRemaining
               READ numQuestionsRemaining
               NOTIFY numQuestionsRemainingChanged
               FINAL)
    Q_PROPERTY(QString state // TODO enum?
               READ state
               NOTIFY stateChanged
               FINAL)
    // clang-format on
    QML_ELEMENT

public:
    explicit QuizBackend(QObject *parent = nullptr);

    QString localeName();
    double voiceRate();
    QString question();
    int numQuestionsRemaining();
    QString state();

    Q_INVOKABLE void invokeQuizSetup(const bool &ttsError);
    Q_INVOKABLE void startQuiz();
    Q_INVOKABLE void check(const QString input);
    Q_INVOKABLE void setUnavailable();
    Q_INVOKABLE void setStateToAvailability();

signals:
    void localeNameChanged();
    void voiceRateChanged();
    void numQuestionsRemainingChanged();
    void questionChanged();
    void stateChanged();
    void ttsErrorFound();

private:
    void nextQuestion();
    void setupQuiz();
    bool isAvailable();
    void setStateToCompleted();

    Tts::QuizTranslator translator_;
    bool viewIsAvailable_;
    TimesTables::Quiz quiz_;
    QString questionBase_;
    QString state_;
};

#endif // OTTQ_20250829_1810_INCLUDE
