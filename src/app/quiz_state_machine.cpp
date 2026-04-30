#include "quiz_state_machine.hpp"
#include <QTextToSpeech>
#include <stdexcept>

QuizStateMachine::QuizStateMachine(QObject *parent)
    : QStateMachine(parent), state_("setting-up")
{
    setup();
}

void QuizStateMachine::setup()
{
    addState(&setup_);
    addState(&c_);
    addState(&loading_);
    addState(&synthesizing_);
    addState(&unavailable_);
    addState(&available_);
    addState(&completed_);
    addState(&end_);

    setInitialState(&setup_);

    setup_.assignProperty(this, "state", "setting-up");
    c_.assignProperty(this, "state", "setting-up");
    loading_.assignProperty(this, "state", "tts-loading");
    synthesizing_.assignProperty(this, "state", "tts-synthesizing");
    unavailable_.assignProperty(this, "state", "unavailable");
    available_.assignProperty(this, "state", "available");
    completed_.assignProperty(this, "state", "completed");

    setupTransitions();
}

void QuizStateMachine::setupTransitions()
{
    setup_.addTransition(this, &QuizStateMachine::error, &unavailable_);
    setup_.addTransition(this, &QuizStateMachine::setupDone, &c_);
    c_.addTransition(this, &QuizStateMachine::ttsUnavailable, &loading_);
    c_.addTransition(this, &QuizStateMachine::ttsAvailable, &synthesizing_);

    QObject::connect(&c_, &QState::entered, this, [this]() {
        if (ttsError_)
            emit ttsUnavailable();
        else
            emit ttsAvailable();
    });
    // TODO is there a better way to account for the tts state for the
    // transition?

    loading_.addTransition(this, &QuizStateMachine::ttsReady, &synthesizing_);
    synthesizing_.addTransition(
        this, &QuizStateMachine::ttsSpeaking, &available_);

    synthesizing_.addTransition(this, &QuizStateMachine::error, &unavailable_);
    available_.addTransition(this, &QuizStateMachine::error, &unavailable_);
    available_.addTransition(this, &QuizStateMachine::completed, &completed_);

    unavailable_.addTransition(&end_);
    completed_.addTransition(&end_);
}

void QuizStateMachine::setSetupFunc(std::function<void()> func)
{
    QObject::connect(&setup_, &QState::entered, this, [this, func]() {
        try {
            func();

            emit setupDone();
        } catch (const std::domain_error &e) {
            emit error();
        }
    });
}

void QuizStateMachine::setTtsInitFunc(std::function<void()> func)
{
    QObject::connect(&synthesizing_, &QState::entered, this, [this, func]() {
        try {
            func();
        } catch (const std::domain_error &e) {
            emit error();
        }
    });
}

void QuizStateMachine::setToError()
{
    emit error();
}

void QuizStateMachine::setCompleted()
{
    emit completed();
}

void QuizStateMachine::setToTtsReady()
{
    ttsError_ = false;
    emit ttsReady();
}

void QuizStateMachine::setToTtsSpeaking()
{
    ttsError_ = false;
    emit ttsSpeaking();
}

void QuizStateMachine::setToTtsError()
{
    ttsError_ = true;
}

void QuizStateMachine::stop()
{
    // When navigating back the SM is stopped. Reset the ui state to the initial
    // state.
    setState("setting-up");
    QStateMachine::stop();
}

QString QuizStateMachine::state()
{
    return state_;
}

void QuizStateMachine::setState(const QString &s)
{
    if (state_ == s)
        return;

    state_ = s;
    emit stateChanged();
}
