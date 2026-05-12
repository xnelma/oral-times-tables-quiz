#include "quiz_backend.hpp"
#include <QtLogging>

QuizBackend::QuizBackend(QObject *parent) : QObject(parent)
{
    setupStateMachine();
}

void QuizBackend::setupStateMachine()
{
    machine_ = std::make_unique<QuizStateMachine>(this);

    connect(machine_.get(),
            &QuizStateMachine::stateChanged,
            this,
            &QuizBackend::stateChanged);
    connect(machine_.get(),
            &QStateMachine::stopped,
            this,
            &QuizBackend::stateChanged);

    auto setupTranslation = [this]() {};
    machine_->setSetupFunc([this, setupTranslation]() { setupTranslation(); });

    auto setupTts = [this]() { emit setup(); };
    auto synthesizeFirstQuestion = [this]() { emit firstQuestion(); };
    machine_->setTtsInitFunc([this, setupTts, synthesizeFirstQuestion]() {
        setupTts();
        synthesizeFirstQuestion();
    });
}

void QuizBackend::startStateMachine()
{
    if (!machine_)
        setupStateMachine();
    // TODO RAII

    machine_->start();
}

void QuizBackend::stopStateMachine()
{
    if (!machine_)
        return;

    machine_->stop();
}

void QuizBackend::ttsReady()
{
    machine_->setToTtsReady();
}

void QuizBackend::ttsSpeaking()
{
    machine_->setToTtsSpeaking();
}

void QuizBackend::error()
{
    machine_->setToError();
}

void QuizBackend::quizCompleted()
{
    machine_->setCompleted();
}

// getters and setters for properties:

QString QuizBackend::state()
{
    return machine_ ? machine_->state() : "setting-up";
    // 'setting-up' not 'unavailable' because an empty SM pointer indicates
    // part of the setup: creating the SM instance.
}
