#include "quiz_backend.hpp"
#include "timestables/question.hpp"
#include <QtLogging>

QuizBackend::QuizBackend(QObject *parent)
    : QObject(parent),
#ifdef QT_TRANSLATOR
      translator_(Tts::SelfUpdatingTranslator(this))
#else
      translator_(Tts::SelfUpdatingTranslator())
#endif
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

    auto setupTranslation = [this]() {
        try {
            questionBase_ = translator_.translate(TimesTables::question);
            emit localeNameChanged();
        } catch (const std::invalid_argument &e) {
            qCritical("Translation setup failed: %s", e.what());
            throw std::domain_error(e.what());
        } catch (const std::runtime_error &e) {
            qCritical("Translation setup failed: %s", e.what());
            throw std::domain_error(e.what());
        }
    };
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

QString QuizBackend::localeName()
{
    return QString::fromStdString(translator_.locale().name());
}

double QuizBackend::voiceRate()
{
    return settings_.loadVoiceRateSetting();
}
