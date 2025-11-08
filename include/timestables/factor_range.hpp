#ifndef OTTQ_20250831_1137_INCLUDE
#define OTTQ_20250831_1137_INCLUDE

namespace TimesTables {

struct FactorRange
{
    FactorRange() : first(1), second(20) { }
    // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
    FactorRange(const int f, const int s) : first(f), second(s) { }

    int first;
    int second;
};

} // namespace TimesTables

#endif // OTTQ_20250831_1137_INCLUDE
