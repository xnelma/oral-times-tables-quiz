#include "quiz_settings.hpp"

TimesTables::Settings::Settings()
    : factorRange_(std::make_shared<FactorRange>())
{
}

QList<int> TimesTables::Settings::timesTables()
{
    return timesTables_;
}

auto TimesTables::Settings::factorRange() -> std::shared_ptr<FactorRange>
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
    factorRange_->from = min;
}

void TimesTables::Settings::setMaxFactor(const int max)
{
    factorRange_->to = max;
}
