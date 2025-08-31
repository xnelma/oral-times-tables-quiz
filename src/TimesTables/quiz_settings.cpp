#include "quiz_settings.hpp"

QList<int> TimesTables::Settings::timesTables()
{
    return timesTables_;
}

auto TimesTables::Settings::factorRange() -> FactorRange
{
    return factorRange_;
}

void TimesTables::Settings::addTimesTable(const int number)
{
    if (timesTables_.contains(number))
        return;

    timesTables_.push_back(number);
}

void TimesTables::Settings::setMinFactor(const int min)
{
    factorRange_.from = min;
}

void TimesTables::Settings::setMaxFactor(const int max)
{
    factorRange_.to = max;
}
