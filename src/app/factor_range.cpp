#include "factor_range.hpp"
#include "timestables/factor_range.hpp"

FactorRange::FactorRange() { } // NOLINT

FactorRange::FactorRange(std::shared_ptr<TimesTables::Settings> quizSettings)
    : quizSettings_(quizSettings)
{
}

int FactorRange::min() const
{
    if (quizSettings_ == nullptr)
        return 0; // TODO error handling
    return quizSettings_->factorRange().from;
}

int FactorRange::max() const
{
    if (quizSettings_ == nullptr)
        return 0;
    return quizSettings_->factorRange().to;
}

void FactorRange::setMin(const int min) const
{
    if (quizSettings_ == nullptr || quizSettings_->factorRange().from == min)
        return;
    quizSettings_->setMinFactor(min);
}

void FactorRange::setMax(const int max) const
{
    if (quizSettings_ == nullptr || quizSettings_->factorRange().to == max)
        return;
    quizSettings_->setMaxFactor(max);
}

bool FactorRange::operator==(const FactorRange &fr)
{
    return min() == fr.min() && max() == fr.max();
}
