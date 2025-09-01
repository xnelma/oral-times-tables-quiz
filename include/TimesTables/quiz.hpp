#ifndef QUIZ_HPP
#define QUIZ_HPP

#include "factor_range.hpp"
#include "question.hpp"
#include <QList>
#include <queue>

namespace TimesTables {

class Quiz
{
public:
    void reset(QList<int> timesTables, FactorRange factorRange);
    bool nextQuestion(Question &question);
    bool checkAnswer(int product);

    int numQuestionsRemaining();

private:
    void generateQuestions(QList<int> timesTables, FactorRange factorRange);

    std::queue<Question> questions_;
};

} // namespace TimesTables

#endif // QUIZ_HPP
