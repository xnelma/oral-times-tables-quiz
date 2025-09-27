#ifndef OTTQ_20250831_1138_INCLUDE
#define OTTQ_20250831_1138_INCLUDE

#include "factor_range.hpp"
#include <QList>
#include <memory>

namespace TimesTables {

class Settings
{
public:
    Settings();

    QList<int> timesTables();
    std::shared_ptr<TimesTables::FactorRange> factorRange();

    void addTimesTable(const int number);
    void setMinFactor(const int min);
    void setMaxFactor(const int max);

private:
    QList<int> timesTables_;
    std::shared_ptr<FactorRange> factorRange_;
};

} // namespace TimesTables

#endif // OTTQ_20250831_1138_INCLUDE
