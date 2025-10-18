#include "quiz_backend.hpp"
#include "tts_state_transition.hpp"
#include "tts_singleton.hpp"
#include "tts/tts_settings.hpp"
#include "timestables/factor_range.hpp"
#include "timestables/question.hpp"
#include <QtLogging>
#include <QStateMachine>
#include <QFinalState>

QuizBackend::QuizBackend(QObject *parent)
    : QObject(parent), questionBase_("%1 times %2"), state_("unavailable")
{
    setupStateMachine();
}

void QuizBackend::setupStateMachine()
{
    // NOLINTBEGIN TODO
    auto *machine = new QStateMachine(this);
    auto *setup = new QState();
    auto *setupQuiz = new QState(setup);
    auto *setupTranslation = new QState(setup);
    auto *loading = new QState();
    auto *synthesizing = new QState();
    auto *unavailable = new QState();
    auto *available = new QState();
    auto *waiting = new QState(available);
    auto *talking = new QState(available);
    auto *completed = new QState();
    auto *end = new QFinalState();
    // NOLINTEND

    setup->setInitialState(setupQuiz);
    available->setInitialState(waiting);

    unavailable->addTransition(end);
    completed->addTransition(end);

    setup->assignProperty(this, "state", "unavailable");
    loading->assignProperty(this, "state", "tts-loading");
    synthesizing->assignProperty(this, "state", "tts-synthesizing");
    unavailable->assignProperty(this, "state", "unavailable");
    waiting->assignProperty(this, "state", "available");
    talking->assignProperty(this, "state", "talking");
    completed->assignProperty(this, "state", "completed");

    // transitions
    setup->addTransition(this, &QuizBackend::error, unavailable);
    setupQuiz->addTransition(
        this, &QuizBackend::setupStepDone, setupTranslation);
    setupTranslation->addTransition(
        this, &QuizBackend::setupDoneAndTtsError, loading);
    setupTranslation->addTransition(
        this, &QuizBackend::setupDoneAndTtsReady, synthesizing);

    auto *tts_ready = new TtsStateTransition(TtsSingleton::instance().get(),
                                             QTextToSpeech::Ready);
    tts_ready->setTargetState(synthesizing);
    loading->addTransition(tts_ready);

    auto *tts_speaking = new TtsStateTransition(TtsSingleton::instance().get(),
                                                QTextToSpeech::Speaking);
    tts_speaking->setTargetState(available);
    synthesizing->addTransition(tts_speaking);
    synthesizing->addTransition(this, &QuizBackend::error, unavailable);

    auto *tts_ready2 = new TtsStateTransition(TtsSingleton::instance().get(),
                                              QTextToSpeech::Ready);
    tts_ready2->setTargetState(waiting);
    talking->addTransition(tts_ready2); // TODO maybe binding is a better idea.
    // Additionally, this transition won't work for the first question, as it
    // is in a different parent state.
    auto *tts_speaking2 = new TtsStateTransition(TtsSingleton::instance().get(),
                                                 QTextToSpeech::Speaking);
    tts_speaking2->setTargetState(talking);
    waiting->addTransition(tts_speaking2);
    available->addTransition(this, &QuizBackend::error, unavailable);
    available->addTransition(this, &QuizBackend::completed, completed);

    // connections for defining/calling slots on state change
    QObject::connect(
        setupQuiz, &QState::entered, this, &QuizBackend::setupQuiz);
    QObject::connect(setupTranslation,
                     &QState::entered,
                     this,
                     &QuizBackend::setupTranslation);
    QObject::connect(synthesizing, &QState::entered, this, [this]() {
        setupTts();
        synthesizeFirstQuestion();
    });

    machine->addState(setup);
    machine->addState(loading);
    machine->addState(synthesizing);
    machine->addState(unavailable);
    machine->addState(available);
    machine->addState(completed);
    machine->addState(end);

    machine->setInitialState(setup);

    machine->start(); // TODO if I end up using member variables instead of
    // pointers, move start() out of the method.
}

void QuizBackend::setupQuiz() // TODO remove the grouped state again
{
    try {
        quiz_.setup();
        emit numQuestionsRemainingChanged();
        emit setupStepDone();
    } catch (std::out_of_range &e) {
        qCritical("Quiz setup failed: %s", e.what());
        emit error(); // TODO give information about error in UI
    }
}

void QuizBackend::setupTranslation()
{
    try {
        translator_.translate(questionBase_);

        if (TtsSingleton::instance().isReady())
            emit setupDoneAndTtsReady();
        else
            emit setupDoneAndTtsError();
    } catch (std::runtime_error &e) {
        qCritical("Translation setup failed: %s", e.what());
        emit error();
    }
}

void QuizBackend::setupTts()
{
    Tts::Settings settings;
    double voiceRate = settings.loadVoiceRateSetting();
    TtsSingleton::instance().setup(translator_.locale(), voiceRate);
    if (TtsSingleton::instance().get()->state() == QTextToSpeech::Error) {
        // couldn't set translation
        emit error();
        emit showLocaleError(); // TODO move to state?
        return;
    }
}

void QuizBackend::synthesizeFirstQuestion()
{
    TtsSingleton::instance().say(question());
}

QString QuizBackend::question()
{
    try {
        TimesTables::Question q = quiz_.question();
        return questionBase_.arg(q.factor).arg(q.number);
    } catch (std::out_of_range &e) {
        qCritical("Could not get the question: %s", e.what());
        emit error();
    }

    return "";
}

// behavior in state 'available':

void QuizBackend::check(const QString input)
{
    if (input == "")
        return;

    bool valid = false, correct = false;
    int inputNum = input.toInt(&valid);
    try {
        correct = quiz_.answerIsCorrect(inputNum);
    } catch (std::out_of_range &e) {
        qCritical("Could not check input: %s", e.what());
        emit error();
    }

    if (valid && correct)
        nextQuestion();
}

void QuizBackend::nextQuestion()
{
    if (quiz_.next()) {
        emit questionChanged();
        emit numQuestionsRemainingChanged();
        TtsSingleton::instance().say(question());
    } else {
        emit completed();
    }
}

void QuizBackend::askAgain()
{
    TtsSingleton::instance().say(question());
}

// getters and setters for properties:

QString QuizBackend::state()
{
    return state_;
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

int QuizBackend::numQuestionsRemaining()
{
    std::size_t num = quiz_.numQuestionsRemaining();
    if (num <= INT_MAX)
        return static_cast<int>(num);

    qCritical("number of questions remaining is larger than INT_MAX");
    // (shouldn't be possible)
    return INT_MAX;
}
