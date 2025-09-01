#include "quiz_backend.hpp"
#include "placeholder.hpp"
#include "tts_settings.hpp"
#include "quiz_configuration.hpp"
#include "factor_range.hpp"
#include "question.hpp"

QuizBackend::QuizBackend(QObject *parent)
    : QObject(parent), isAvailable_(true), questionBase_("%1 times %2")
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

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
void QuizBackend::startQuiz(const QList<int> tables, const int minFactor,
                            const int maxFactor)
{
    quiz_.reset(tables, TimesTables::FactorRange(minFactor, maxFactor));
    translator_.translate(questionBase_);

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
    if (TimesTables::Question q; quiz_.nextQuestion(q)) {
        emit questionChanged(questionBase_.arg(q.number).arg(q.factor));
    } else {
        // Shouldn't happen because at least one question should be in the list
        // after setup.
        isAvailable_ = false;
        emit availabilityChanged();
    }
}

bool QuizBackend::isAvailable()
{
    return isAvailable_ && translator_.isAvailable();
}

int QuizBackend::numQuestionsRemaining()
{
    return 1;
}

void QuizBackend::setAvailability(const bool &isAvailable)
{
    if (isAvailable == isAvailable_)
        return;

    isAvailable_ = isAvailable;
    emit availabilityChanged();
}
