#ifndef OTTQ_20102025_1743_INCLUDE
#define OTTQ_20102025_1743_INCLUDE

#include "tts_state_transition.hpp"
#include <QStateMachine>
#include <QState>
#include <QFinalState>
#include <QString>
#include <memory>
#include <functional>

class QuizStateMachine : public QStateMachine
{
    Q_OBJECT
    // clang-format off
    Q_PROPERTY(QString state // TODO enum/constants?
               READ state
               WRITE setState
               NOTIFY stateChanged
               FINAL)
    // clang-format on

public:
    explicit QuizStateMachine(
        QObject *parent = nullptr,
        std::shared_ptr<const QTextToSpeech> tts = nullptr);

    QString state();
    void setState(const QString &s);

    void setSetupFunc(std::function<void()> func);
    void setTtsInitFunc(std::function<void()> func);
    void setToError();
    void setCompleted();

signals:
    void stateChanged();

    void error();
    void setupDone();
    void ttsUnavailable();
    void ttsAvailable();
    void completed();

private:
    void setup();
    void setupTransitions();

    QString state_;

    std::shared_ptr<const QTextToSpeech> tts_;

    QState setup_;
    QState c_;
    QState loading_;
    QState synthesizing_;
    QState unavailable_;
    QState available_;
    QState completed_;
    QFinalState end_;
    TtsStateTransition tts_ready_;
    TtsStateTransition tts_speaking_;
};

#endif // OTTQ_20102025_1743_INCLUDE
