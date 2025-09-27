#include "quiz_configuration.hpp"

QuizConfiguration::QuizConfiguration(QObject *parent)
    : QObject(parent),
      quizSettings_(std::make_shared<TimesTables::Settings>()),
      factorRange_(FactorRange(quizSettings_->factorRange()))
{
}

QString QuizConfiguration::timesTablesStr()
{
    QString timesTables;
    for (const int n : quizSettings_->timesTables())
        timesTables += QString::number(n) + ", ";

    if (timesTables.length() < 2)
        return "";
    return timesTables.first(timesTables.length() - 2);
}

QList<int> QuizConfiguration::timesTables()
{
    return quizSettings_->timesTables();
}

FactorRange QuizConfiguration::factorRange() const
{
    return factorRange_;
}

void QuizConfiguration::setFactorRange(const FactorRange &fr)
{
    if (factorRange_ == fr)
        return;

    factorRange_ = fr;
    emit factorRangeChanged();
}

void QuizConfiguration::addTimesTable(const int number)
{
    quizSettings_->addTimesTable(number);

    emit timesTablesStrChanged();
}
