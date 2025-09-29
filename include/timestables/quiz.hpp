#ifndef OTTQ_20250901_2055_INCLUDE
#define OTTQ_20250901_2055_INCLUDE

#include "factor_range.hpp"
#include "question.hpp"
#include <QList>
#include <vector>
#include <memory>

namespace TimesTables {

typedef std::shared_ptr<FactorRange> FactorRangePtr;

class Quiz
{
public:
    void setup();
    bool isAvailable();
    Question question();
    bool next();
    bool answerIsCorrect(const int answer);

    std::size_t numQuestionsRemaining();

private:
    void generateQuestions();

    std::vector<Question> questions_;
};

} // namespace TimesTables

#endif // OTTQ_20250901_2055_INCLUDE
