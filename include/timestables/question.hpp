#ifndef OTTQ_20250901_2054_INCLUDE
#define OTTQ_20250901_2054_INCLUDE

namespace TimesTables {

static const char *const question = "%1 times %2";

struct Question
{
    bool check(const int product) { return factor * number == product; }

    int number;
    int factor;
};

} // namespace TimesTables

#endif // OTTQ_20250901_2054_INCLUDE
