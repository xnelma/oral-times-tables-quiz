#include "quiz.hpp"
#include <ranges>
#include <random>

Quiz::Quiz(QObject *parent) : QObject{ parent } { }

void Quiz::setup(const QuizConfiguration &qc)
{
    questions_.clear();

    if (qc.timesTables().empty())
        throw std::out_of_range("tables are empty");
    // TODO handle exception

    generateQuestions(qc);
}

void Quiz::generateQuestions(const QuizConfiguration &qc)
{
    const auto range = qc.factorRange();
    const auto tables = qc.timesTables();

    const auto factors =
        std::ranges::iota_view{ range.first(), range.second() + 1 };
    for (const int number : tables)
        for (const int factor : factors)
            questions_.push_back(Question(/*this,*/ number, factor));

    std::mt19937 gen{ std::random_device{}() };
    std::ranges::shuffle(questions_, gen);
    emit questionChanged();
    emit numQuestionsRemainingChanged();
}

Question Quiz::question()
{
    if (questions_.empty())
        throw std::out_of_range("questions_ is empty");
    return questions_.back();
}

bool Quiz::next()
{
    questions_.pop_back();
    emit questionChanged();
    emit numQuestionsRemainingChanged();
    return !questions_.empty();
}

bool Quiz::answerIsCorrect(const int answer)
{
    if (questions_.empty())
        throw std::out_of_range("questions_ is empty");
    return questions_.back().check(answer);
}

qsizetype Quiz::numQuestionsRemaining()
{
    return questions_.empty() ? 0 : questions_.size() - 1;
}
