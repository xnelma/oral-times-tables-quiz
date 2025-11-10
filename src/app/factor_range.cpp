#include "factor_range.hpp"
#include "timestables/factor_range.hpp"

FactorRange::FactorRange()
    : factorRange_(std::make_shared<TimesTables::FactorRange>())
{
}

FactorRange::FactorRange(std::shared_ptr<TimesTables::FactorRange> fr)
    : factorRange_(fr)
{
}

int FactorRange::first() const
{
    return factorRange_->first;
}

int FactorRange::second() const
{
    return factorRange_->second;
}

std::shared_ptr<TimesTables::FactorRange> FactorRange::get() const
{
    return factorRange_;
}

void FactorRange::setFirst(const int first) const
{
    if (factorRange_->first == first)
        return;
    factorRange_->first = first;
}

void FactorRange::setSecond(const int second) const
{
    if (factorRange_->second == second)
        return;
    factorRange_->second = second;
}

bool FactorRange::operator==(const FactorRange &fr)
{
    return first() == fr.first() && second() == fr.second();
}
