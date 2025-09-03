#include "quiz_backend.hpp"
#include "placeholder.hpp"
#include "tts_settings.hpp"
#include "quiz_configuration.hpp"
#include "factor_range.hpp"
#include "question.hpp"
#include <QtLogging>

QuizBackend::QuizBackend(QObject *parent)
    : QObject(parent), isAvailable_(false), questionBase_("%1 times %2")
{
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

bool QuizBackend::isAvailable()
{
    return isAvailable_ && translator_.isAvailable();
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

void QuizBackend::setAvailability(const bool &isAvailable)
{
    if (isAvailable == isAvailable_)
        return;

    isAvailable_ = isAvailable;
    emit availabilityChanged();
}

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
void QuizBackend::startQuiz(const QList<int> tables, const int minFactor,
                            const int maxFactor)
{
    quiz_.reset(tables, TimesTables::FactorRange(minFactor, maxFactor));
    translator_.translate(questionBase_);

    try {
        TimesTables::Question q = quiz_.firstQuestion();
        setAvailability(true);
        emit questionChanged(questionBase_.arg(q.factor).arg(q.number));
        emit numQuestionsRemainingChanged();
    } catch (std::out_of_range &e) {
        setAvailability(false);
        qCritical("Couldn't get the first question: %s", e.what());
    }
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
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
    if (TimesTables::Question q; quiz_.nextQuestion(q)) {
        emit questionChanged(questionBase_.arg(q.factor).arg(q.number));
        emit numQuestionsRemainingChanged();
    } else {
        emit quizCompleted();
    }
}
