#include "quiz_config.hpp"

QList<int> QuizConfiguration::timesTables()
{
    return timesTables_;
}

QString QuizConfiguration::timesTablesStr()
{
    QString timesTables;
    for (const int n : timesTables_)
        timesTables += QString::number(n) + ", ";

    if (timesTables.length() < 2)
        return "";
    return timesTables.first(timesTables.length() - 2);
}

FactorRange QuizConfiguration::factorRange()
{
    return factorRange_;
}

void QuizConfiguration::setFactorRange(const FactorRange &fr)
{
    if (fr == factorRange_)
        return;

    factorRange_ = fr;
}

void QuizConfiguration::addTimesTable(const int number)
{
    if (timesTables_.contains(number))
        return;

    timesTables_.push_back(number);
}
