#include "quiz_backend.hpp"
#include "tts/tts_settings.hpp"
#include "timestables/factor_range.hpp"
#include "timestables/question.hpp"
#include <QtLogging>

QuizBackend::QuizBackend(QObject *parent)
    : QObject(parent),
      viewIsAvailable_(true),
      questionBase_("%1 times %2"),
      state_("unavailable")
{
}

void QuizBackend::invokeQuizSetup(const bool &ttsError)
{
    bool ok = setupQuiz();
    if (!ok) {
        state_ = "unavailable";
    } else if (ttsError) {
        state_ = "tts-loading";
        emit ttsErrorFound();
    } else {
        state_ = "available";
        startQuiz();
    }

    emit stateChanged();
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

QString QuizBackend::localeName()
{
    return translator_.locale().name();
}

double QuizBackend::voiceRate()
{
    // Is only called once at setup
    Tts::Settings settings;
    return settings.loadVoiceRateSetting();
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

bool QuizBackend::setupQuiz()
{
    quiz_.setup();
    translator_.translate(questionBase_);
    return quiz_.isAvailable() && translator_.isAvailable();
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
