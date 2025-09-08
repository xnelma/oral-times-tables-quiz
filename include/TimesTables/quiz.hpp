#ifndef QUIZ_HPP
#define QUIZ_HPP

#include "factor_range.hpp"
#include "question.hpp"
#include <QList>
#include <vector>

namespace TimesTables {

class Quiz
{
public:
    void setup(const QList<int> timesTables, const FactorRange factorRange);
    bool isAvailable();
    Question question();
    bool next();
    bool answerIsCorrect(const int answer);

    std::size_t numQuestionsRemaining();

private:
    void generateQuestions(const QList<int> timesTables,
                           const FactorRange factorRange);

    std::vector<Question> questions_;
};

} // namespace TimesTables

#endif // QUIZ_HPP
