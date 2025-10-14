#include "quiz_backend.hpp"
#include "tts_state_transition.hpp"
#include "tts_singleton.hpp"
#include "tts/tts_settings.hpp"
#include "timestables/factor_range.hpp"
#include "timestables/question.hpp"
#include <QtLogging>
#include <QStateMachine>

QuizBackend::QuizBackend(QObject *parent)
    : QObject(parent),
      viewIsAvailable_(true),
      questionBase_("%1 times %2"),
      state_("unavailable")
{
    setupQuiz();
    startQuiz();

    setupStateMachine();
}

void QuizBackend::setupStateMachine()
{
    // NOLINTBEGIN TODO
    auto *machine = new QStateMachine(this);
    auto *loading = new QState();
    auto *synthesizing = new QState();
    auto *unavailable = new QState();
    auto *available = new QState();
    auto *completed = new QState();
    // NOLINTEND

    loading->assignProperty(this, "state", "tts-loading");
    synthesizing->assignProperty(this, "state", "tts-synthesizing");
    unavailable->assignProperty(this, "state", "unavailable");
    available->assignProperty(this, "state", "available");
    completed->assignProperty(this, "state", "completed");

    // transitions
    auto *tts_ready = new TtsStateTransition(TtsSingleton::instance().get(),
                                             QTextToSpeech::Ready);
    tts_ready->setTargetState(synthesizing);
    loading->addTransition(tts_ready);

    auto *tts_speaking = new TtsStateTransition(TtsSingleton::instance().get(),
                                                QTextToSpeech::Speaking);
    tts_speaking->setTargetState(available /* or unavailable */);
    synthesizing->addTransition(tts_speaking);

    // connections for defining/calling slots on state change
    QObject::connect(synthesizing, &QState::entered, this, [this]() {
        Tts::Settings settings;
        double voiceRate = settings.loadVoiceRateSetting();
        TtsSingleton::instance().setup(translator_.locale(), voiceRate);

        TtsSingleton::instance().say(question());
    });

    machine->addState(loading);
    machine->addState(synthesizing);
    machine->addState(unavailable);
    machine->addState(available);
    machine->addState(completed);

    machine->setInitialState(TtsSingleton::instance().isReady() ? synthesizing
                                                                : loading);

    machine->start();
}

void QuizBackend::setUnavailable()
{
    viewIsAvailable_ = false;
    state_ = "unavailable";
    emit stateChanged();
}

void QuizBackend::setStateToAvailability()
{
    state_ = isAvailable() ? "available" : "unavailable";
    emit stateChanged();
}

void QuizBackend::setStateToCompleted()
{
    state_ = "completed";
    emit stateChanged();
}

void QuizBackend::setState(const QString &s)
{
    if (state_ == s)
        return;

    state_ = s;
    emit stateChanged();
}

QString QuizBackend::localeName()
{
    return translator_.locale().name();
}

QString QuizBackend::question()
{
    try {
        TimesTables::Question q = quiz_.question();
        return questionBase_.arg(q.factor).arg(q.number);
    } catch (std::out_of_range &e) {
        setUnavailable();
        qCritical("Couldn't get the question: %s", e.what());
    }

    return "";
}

bool QuizBackend::isAvailable()
{
    return viewIsAvailable_ && translator_.isAvailable() && quiz_.isAvailable();
}

int QuizBackend::numQuestionsRemaining()
{
    std::size_t num = quiz_.numQuestionsRemaining();
    if (num <= INT_MAX)
        return static_cast<int>(num);

    qCritical("number of questions remaining is larger than INT_MAX");
    // (shouldn't be possible)
    return INT_MAX;
}

QString QuizBackend::state()
{
    return state_;
}

bool QuizBackend::ttsReady()
{
    return TtsSingleton::instance().isReady();
    // TODO binding will not work like this.
    // I would need a state change connecting to the tts speaking state
}

void QuizBackend::setupQuiz()
{
    quiz_.setup();
    translator_.translate(questionBase_);
}

void QuizBackend::startQuiz()
{
    emit questionChanged();
    emit numQuestionsRemainingChanged();
}

void QuizBackend::check(const QString input)
{
    if (input == "")
        return;

    bool valid = false, correct = false;
    int inputNum = input.toInt(&valid);
    try {
        correct = quiz_.answerIsCorrect(inputNum);
    } catch (std::out_of_range &e) {
        // TODO show an error dialog
        qCritical("Couldn't check input: %s", e.what());
    }

    if (valid && correct)
        nextQuestion();
}

void QuizBackend::nextQuestion()
{
    if (quiz_.next()) {
        emit questionChanged();
        emit numQuestionsRemainingChanged();
    } else {
        setStateToCompleted();
    }
}

void QuizBackend::askAgain()
{
    TtsSingleton::instance().say(question());
}
