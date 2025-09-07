#include "quiz.hpp"
#include <ranges>
#include <random>

void TimesTables::Quiz::setup(const QList<int> timesTables,
                              const FactorRange factorRange)
{
    questions_.clear();
    generateQuestions(timesTables, factorRange);
}

bool TimesTables::Quiz::isAvailable()
{
    return !questions_.empty();
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

auto TimesTables::Quiz::question() -> Question
{
    if (questions_.empty())
        throw std::out_of_range("questions_ is empty");
    return questions_.back();
}

bool TimesTables::Quiz::next()
{
    questions_.pop_back();
    return !questions_.empty();
}

bool TimesTables::Quiz::answerIsCorrect(const int answer)
{
    if (questions_.empty())
        throw std::out_of_range("questions_ is empty");
    return questions_.back().check(answer);
}

std::size_t TimesTables::Quiz::numQuestionsRemaining()
{
    return questions_.empty() ? 0 : questions_.size() - 1;
}
