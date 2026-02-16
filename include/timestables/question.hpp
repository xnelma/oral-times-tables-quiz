#ifndef OTTQ_20250901_2054_INCLUDE
#define OTTQ_20250901_2054_INCLUDE

#if defined BOOST_TRANSLATOR
#  include <boost/locale.hpp>
#endif

namespace TimesTables {

#if defined BOOST_TRANSLATOR
static const boost::locale::basic_message<char> question =
    boost::locale::translate("{} times {}");
#else
static const char *const question = "{} times {}";
#endif

struct Question
{
    bool check(const int product) { return factor * number == product; }

    int number;
    int factor;
};

} // namespace TimesTables

#endif // OTTQ_20250901_2054_INCLUDE
