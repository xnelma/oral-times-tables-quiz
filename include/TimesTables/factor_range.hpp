#ifndef FACTOR_RANGE_HPP
#define FACTOR_RANGE_HPP

namespace TimesTables {

struct FactorRange
{
    FactorRange() : from(1), to(20) { }
    // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
    FactorRange(const int min, const int max) : from(min), to(max) { }

    int from;
    int to;
};

} // namespace TimesTables

#endif // FACTOR_RANGE_HPP
