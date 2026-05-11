#ifndef OTTQ_20250829_1810_INCLUDE
#define OTTQ_20250829_1810_INCLUDE

#include "quiz_state_machine.hpp"
#include "tts/tts_settings.hpp"
#include <QObject>
#include <qqml.h>
#include <QLocale>
#include <QString>
#include <QTextToSpeech>
#include <memory>

class QuizBackend : public QObject
{
    Q_OBJECT
    // clang-format off
    Q_PROPERTY(double voiceRate
               READ voiceRate
               NOTIFY voiceRateChanged
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
    double voiceRate();

    Q_INVOKABLE void startStateMachine();
    Q_INVOKABLE void stopStateMachine();

    Q_INVOKABLE void ttsReady();
    Q_INVOKABLE void ttsSpeaking();
    Q_INVOKABLE void error();
    Q_INVOKABLE void quizCompleted();

signals:
    void questionChanged();
    void stateChanged();
    void setup();
    void firstQuestion();
    void voiceRateChanged();

private:
    void setupStateMachine();

    std::unique_ptr<QuizStateMachine> machine_;

    Tts::Settings settings_;
    std::string questionBase_;
};

#endif // OTTQ_20250829_1810_INCLUDE
