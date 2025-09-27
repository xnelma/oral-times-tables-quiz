#include "factor_range.hpp"
#include "timestables/factor_range.hpp"
#include <QtLogging>

FactorRange::FactorRange()
    : factorRange_(std::make_shared<TimesTables::FactorRange>())
{
}

FactorRange::FactorRange(std::shared_ptr<TimesTables::FactorRange> fr)
    : factorRange_(fr)
{
}

int FactorRange::min() const
{
    return factorRange_->from;
}

int FactorRange::max() const
{
    return factorRange_->to;
}

void FactorRange::setMin(const int min) const
{
    if (factorRange_->from == min)
        return;
    factorRange_->from = min;
}

void FactorRange::setMax(const int max) const
{
    if (factorRange_->to == max)
        return;
    factorRange_->to = max;
}

bool FactorRange::operator==(const FactorRange &fr)
{
    return min() == fr.min() && max() == fr.max();
}
