#include "quiz.hpp"
#include <ranges>
#include <random>

void TimesTables::Quiz::reset(QList<int> timesTables, FactorRange factorRange)
{
    questions_.clear();
    generateQuestions(timesTables, factorRange);
}

void TimesTables::Quiz::generateQuestions(const QList<int> tables,
                                          const FactorRange range)
{
    auto factors = std::ranges::iota_view{ range.from, range.to + 1 };
    for (const int number : tables)
        for (const int factor : factors)
            questions_.push_back({ number, factor });

    std::mt19937 gen{ std::random_device{}() };
    std::ranges::shuffle(questions_, gen);
}

auto TimesTables::Quiz::firstQuestion() -> Question
{
    return questions_.back();
}

bool TimesTables::Quiz::nextQuestion(Question &question)
{
    questions_.pop_back();
    if (questions_.size() == 0)
        return false;

    question = questions_.back();
    return true;
}

bool TimesTables::Quiz::answerIsCorrect(const int answer)
{
    if (questions_.size() == 0)
        throw std::out_of_range("questions_ is empty");
    return questions_.back().check(answer);
}

std::size_t TimesTables::Quiz::numQuestionsRemaining()
{
    return questions_.size() == 0 ? 0 : questions_.size() - 1;
}
