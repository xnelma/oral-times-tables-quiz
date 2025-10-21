#include "quiz_state_machine.hpp"
#include <QTextToSpeech>
#include <stdexcept>

QuizStateMachine::QuizStateMachine(QObject *parent,
                                   std::shared_ptr<const QTextToSpeech> tts)
    : QStateMachine(parent),
      tts_(tts),
      state_("unavailable"),
      tts_ready_(TtsStateTransition(tts, QTextToSpeech::Ready)),
      tts_speaking_(TtsStateTransition(tts, QTextToSpeech::Speaking))
{
    if (tts == nullptr)
        throw std::domain_error("reference to tts not available in quiz SM");

    setup();
}

void QuizStateMachine::setup()
{
    addState(&setup_);
    addState(&loading_);
    addState(&synthesizing_);
    addState(&unavailable_);
    addState(&available_);
    addState(&completed_);
    addState(&end_);

    setInitialState(&setup_);

    setup_.assignProperty(this, "state", "unavailable");
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
    setup_.addTransition(
        this, &QuizStateMachine::setupDoneAndTtsError, &loading_);
    setup_.addTransition(
        this, &QuizStateMachine::setupDoneAndTtsReady, &synthesizing_);
    // TODO is there a better way to account for the tts state for the
    // transition?

    tts_ready_.setTargetState(&synthesizing_);
    loading_.addTransition(&tts_ready_);

    tts_speaking_.setTargetState(&available_);
    synthesizing_.addTransition(&tts_speaking_);

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

            if (tts_->state() == QTextToSpeech::Ready)
                emit setupDoneAndTtsReady();
            else
                emit setupDoneAndTtsError();
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
