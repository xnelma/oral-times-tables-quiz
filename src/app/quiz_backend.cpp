#include "quiz_backend.hpp"
#include "timestables/factor_range.hpp"
#include "timestables/question.hpp"
#include <QtLogging>

QuizBackend::QuizBackend(QObject *parent)
    : QObject(parent),
      tts_(std::make_shared<QTextToSpeech>(this)),
      translator_(Tts::SelfUpdatingTranslator(this)),
      questionBase_(TimesTables::question)
{
    setupStateMachine();
}

void QuizBackend::setupStateMachine()
{
    machine_ = std::make_unique<QuizStateMachine>(this, tts_);

    connect(machine_.get(),
            &QuizStateMachine::stateChanged,
            this,
            &QuizBackend::stateChanged);
    connect(machine_.get(),
            &QStateMachine::stopped,
            this,
            &QuizBackend::stateChanged);

    auto setupQuiz = [this]() {
        try {
            auto t = quizConfig_.timesTables();
            auto r = quizConfig_.factorRange();
            quiz_.setup(t, TimesTables::FactorRange(r.first(), r.second()));

            emit numQuestionsRemainingChanged();
        } catch (const std::out_of_range &e) {
            qCritical("Quiz setup failed: %s", e.what());
            throw std::domain_error(e.what());
            // TODO give information about error in UI
        }
    };
    auto setupTranslation = [this]() {
        try {
            questionBase_ = translator_.translate(
                QuizConstants::translationContext, TimesTables::question);
            emit localeNameChanged();
        } catch (const std::invalid_argument &e) {
            qCritical("Translation setup failed: %s", e.what());
            throw std::domain_error(e.what());
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
        auto locale = translator_.locale();
        double rate = settings_.loadVoiceRateSetting();
        tts_->setLocale(QLocale(locale.language(), locale.territory()));
        // FIXME QLocale::system() and
        // QLocale(l_sys.language(), l_sys.territory()) compare to different
        // objects, and trying to set the former as tts locale causes tts to
        // get into error state.
        // Before I created a new object in qml anyways, so I did not notice it.
        tts_->setRate(rate);
        if (tts_->state() == QTextToSpeech::Error) {
            // couldn't set translation
            emit showLocaleError();
            throw std::domain_error("could not set tts locale");
        }
    };
    auto synthesizeFirstQuestion = [this]() { sayQuestion(); };
    machine_->setTtsInitFunc([this, setupTts, synthesizeFirstQuestion]() {
        setupTts();
        synthesizeFirstQuestion();
    });
}

void QuizBackend::startStateMachine(const QuizConfiguration &config)
{
    if (!machine_)
        setupStateMachine();
    // TODO RAII

    quizConfig_ = config;
    machine_->start();
}

void QuizBackend::stopStateMachine()
{
    if (!machine_)
        return;

    machine_->stop();
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

        sayQuestion();
    } else {
        // Let last question fade out instead of stopping it.

        machine_->setCompleted();
    }
}

void QuizBackend::sayQuestion()
{
    // Stop current question and start next right away instead of
    // enqueueing. This way the quiz can be faster.
    if (tts_->state() == QTextToSpeech::Speaking) {
        tts_->stop();
        tts_->say(question());
    } else {
        // Enqueue in case tts is not ready (but not due to talking).
        tts_->enqueue(question());
    }
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
