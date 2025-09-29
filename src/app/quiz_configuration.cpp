#include "quiz_configuration.hpp"

QuizConfiguration::QuizConfiguration(QObject *parent)
    : QObject(parent),
      factorRange_(FactorRange(TimesTables::Settings::instance().factorRange()))
{
}

QString QuizConfiguration::timesTablesStr()
{
    QString timesTables;
    for (const int n : TimesTables::Settings::instance().timesTables())
        timesTables += QString::number(n) + ", ";

    if (timesTables.length() < 2)
        return "";
    return timesTables.first(timesTables.length() - 2);
}

QList<int> QuizConfiguration::timesTables()
{
    return TimesTables::Settings::instance().timesTables();
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
    TimesTables::Settings::instance().addTimesTable(number);

    emit timesTablesStrChanged();
}
