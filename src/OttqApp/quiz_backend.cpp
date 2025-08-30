#include "quiz_backend.hpp"
#include "placeholder.hpp"
#include "tts_settings.hpp"

QuizBackend::QuizBackend(QObject *parent)
    : QObject(parent), isAvailable_(true), question_("%1 times %2")
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

QString QuizBackend::getQuestion()
{
    Placeholder p;
    return translator_.translate(question_).arg(p.a).arg(p.b);
}

bool QuizBackend::isAvailable()
{
    return isAvailable_ && translator_.isAvailable();
}

void QuizBackend::setAvailability(const bool &isAvailable)
{
    if (isAvailable == isAvailable_)
        return;

    isAvailable_ = isAvailable;
    emit availabilityChanged();
}
