#ifndef OTTQ_20250901_2054_INCLUDE
#define OTTQ_20250901_2054_INCLUDE

namespace TimesTables {

struct Question
{
    bool check(const int product) { return factor * number == product; }

    int number;
    int factor;
};

} // namespace TimesTables

#endif // OTTQ_20250901_2054_INCLUDE
