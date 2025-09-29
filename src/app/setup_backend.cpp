#include "setup_backend.hpp"

SetupBackend::SetupBackend(QObject *parent)
    : QObject(parent),
      factorRange_(FactorRange(TimesTables::Settings::instance().factorRange()))
{
}

QString SetupBackend::timesTablesStr()
{
    QString timesTables;
    for (const int n : TimesTables::Settings::instance().timesTables())
        timesTables += QString::number(n) + ", ";

    if (timesTables.length() < 2)
        return "";
    return timesTables.first(timesTables.length() - 2);
}

QList<int> SetupBackend::timesTables()
{
    return TimesTables::Settings::instance().timesTables();
}

FactorRange SetupBackend::factorRange() const
{
    return factorRange_;
}

void SetupBackend::setFactorRange(const FactorRange &fr)
{
    if (factorRange_ == fr)
        return;

    factorRange_ = fr;
    emit factorRangeChanged();
}

void SetupBackend::addTimesTable(const int number)
{
    TimesTables::Settings::instance().addTimesTable(number);

    emit timesTablesStrChanged();
}
