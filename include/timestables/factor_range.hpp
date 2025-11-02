#ifndef OTTQ_20250831_1137_INCLUDE
#define OTTQ_20250831_1137_INCLUDE

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

#endif // OTTQ_20250831_1137_INCLUDE
