#ifndef QUESTION_HPP
#define QUESTION_HPP

namespace TimesTables {

struct Question
{
    bool check(const int product) { return factor * number == product; }

    int number;
    int factor;
};

} // namespace TimesTables

#endif // QUESTION_HPP
