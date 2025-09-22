#include "quiz_configuration.hpp"

QuizConfiguration::QuizConfiguration(QObject *parent) : QObject{ parent } { }

QString QuizConfiguration::timesTablesStr()
{
    QString timesTables;
    for (const int n : quizSettings_.timesTables())
        timesTables += QString::number(n) + ", ";

    if (timesTables.length() < 2)
        return "";
    return timesTables.first(timesTables.length() - 2);
}

QList<int> QuizConfiguration::timesTables()
{
    return quizSettings_.timesTables();
}

int QuizConfiguration::minFactor()
{
    return quizSettings_.factorRange().from;
}

int QuizConfiguration::maxFactor()
{
    return quizSettings_.factorRange().to;
}

void QuizConfiguration::setMinFactor(const int min)
{
    if (minFactor() == min)
        return;

    quizSettings_.setMinFactor(min);

    emit minFactorChanged();
}

void QuizConfiguration::setMaxFactor(const int max)
{
    if (maxFactor() == max)
        return;

    quizSettings_.setMaxFactor(max);

    emit maxFactorChanged();
}

void QuizConfiguration::addTimesTable(const int number)
{
    quizSettings_.addTimesTable(number);

    emit timesTablesStrChanged();
}
