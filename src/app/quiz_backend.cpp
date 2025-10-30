#include "quiz_backend.hpp"
#include "tts_singleton.hpp"
#include "tts/tts_settings.hpp"
#include "timestables/factor_range.hpp"
#include "timestables/question.hpp"
#include <QtLogging>

QuizBackend::QuizBackend(QObject *parent) : QObject(parent) { }

void QuizBackend::runStateMachine()
{
    machine_ = std::make_unique<QuizStateMachine>(
        this, TtsSingleton::instance().get());

    connect(machine_.get(),
            &QuizStateMachine::stateChanged,
            this,
            &QuizBackend::stateChanged);

    auto setupQuiz = [this]() {
        try {
            quiz_.setup();
            emit numQuestionsRemainingChanged();
        } catch (const std::out_of_range &e) {
            qCritical("Quiz setup failed: %s", e.what());
            throw std::domain_error(e.what());
            // TODO give information about error in UI
        }
    };
    auto setupTranslation = [this]() {
        try {
            // initialize here instead of in constructor, so the key is
            // available for retranslating in case the locale changed.
            questionBase_ = "%1 times %2";
            translator_.translate(questionBase_);
        } catch (const std::runtime_error &e) {
            qCritical("Translation setup failed: %s", e.what());
            throw std::domain_error(e.what());
        }
    };
    machine_->setSetupFunc([this, setupQuiz, setupTranslation]() {
        setupQuiz();
        setupTranslation();
    });

    auto setupTts = [this]() {
        Tts::Settings settings;
        double voiceRate = settings.loadVoiceRateSetting();
        TtsSingleton::instance().setup(translator_.locale(), voiceRate);
        if (TtsSingleton::instance().get()->state() == QTextToSpeech::Error) {
            // couldn't set translation
            emit showLocaleError();
            throw std::domain_error("could not set tts locale");
        }
    };
    auto synthesizeFirstQuestion = [this]() {
        TtsSingleton::instance().say(question());
    };
    machine_->setTtsInitFunc([this, setupTts, synthesizeFirstQuestion]() {
        setupTts();
        synthesizeFirstQuestion();
    });

    machine_->start();
}

QString QuizBackend::question()
{
    try {
        TimesTables::Question q = quiz_.question();
        return questionBase_.arg(q.factor).arg(q.number);
    } catch (std::out_of_range &e) {
        qCritical("Could not get the question: %s", e.what());
        throw std::domain_error(e.what());
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
        machine_->setToError();
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
        machine_->setCompleted();
    }
}

void QuizBackend::askAgain()
{
    if (TtsSingleton::instance().isReady())
        TtsSingleton::instance().say(question());
}

// getters and setters for properties:

QString QuizBackend::state()
{
    return machine_ ? machine_->state() : "unavailable";
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
