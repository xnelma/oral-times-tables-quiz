#include "setup_backend.hpp"

SetupBackend::SetupBackend(QObject *parent) : QObject{ parent } { }

QString SetupBackend::timesTableNumbers()
{
    QString timesTables;
    for (const int n : quizSettings_.timesTables())
        timesTables += QString::number(n) + ", ";

    if (timesTables.length() < 2)
        return "";
    return timesTables.first(timesTables.length() - 2);
}

int SetupBackend::minFactor()
{
    return quizSettings_.factorRange().from;
}

int SetupBackend::maxFactor()
{
    return quizSettings_.factorRange().to;
}

void SetupBackend::setMinFactor(const int min)
{
    if (minFactor() == min)
        return;

    quizSettings_.setMinFactor(min);

    emit minFactorChanged();
}

void SetupBackend::setMaxFactor(const int max)
{
    if (maxFactor() == max)
        return;

    quizSettings_.setMaxFactor(max);

    emit maxFactorChanged();
}

void SetupBackend::addTimesTable(const int number)
{
    quizSettings_.addTimesTable(number);

    emit timesTablesChanged();
}
