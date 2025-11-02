#include "quiz.hpp"
#include "quiz_settings.hpp"
#include <ranges>
#include <random>

void TimesTables::Quiz::setup()
{
    questions_.clear();
    generateQuestions();
}

void TimesTables::Quiz::generateQuestions()
{
    // TODO getting the data from a singleton just now is a bit sneaky.
    const auto tables = TimesTables::Settings::instance().timesTables();
    if (tables.empty())
        throw std::out_of_range("tables are empty");
    const auto range = TimesTables::Settings::instance().factorRange();

    auto factors = std::ranges::iota_view{ range->from, range->to + 1 };
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
