#include "quiz.hpp"

void TimesTables::Quiz::reset(QList<int> timesTables, FactorRange factorRange)
{
    std::queue<Question>().swap(questions_); // clear questions
    generateQuestions(timesTables, factorRange);
}

void TimesTables::Quiz::generateQuestions(QList<int> timesTables,
                                          FactorRange factorRange)
{
    // randomize
}

bool TimesTables::Quiz::nextQuestion(Question &question)
{
    question = { 2, 7 };
    return true;
}

int TimesTables::Quiz::numQuestionsRemaining()
{
    return 1;
}
