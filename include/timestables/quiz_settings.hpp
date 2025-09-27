#ifndef OTTQ_20250831_1138_INCLUDE
#define OTTQ_20250831_1138_INCLUDE

#include "factor_range.hpp"
#include <QList>

namespace TimesTables {

class Settings
{
public:
    QList<int> timesTables();
    TimesTables::FactorRange factorRange();

    void addTimesTable(const int number);
    void setMinFactor(const int min);
    void setMaxFactor(const int max);

private:
    QList<int> timesTables_;
    FactorRange factorRange_;
};

} // namespace TimesTables

#endif // OTTQ_20250831_1138_INCLUDE
