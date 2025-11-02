#ifndef OTTQ_20250831_1138_INCLUDE
#define OTTQ_20250831_1138_INCLUDE

#include "factor_range.hpp"
#include <QList>
#include <memory>

namespace TimesTables {

class Settings
{
public:
    static Settings &instance();

    Settings(const Settings &) = delete;
    Settings(const Settings &&) = delete;
    Settings &operator=(const Settings &) = delete;
    Settings &operator=(const Settings &&) = delete;

    QList<int> timesTables();
    std::shared_ptr<TimesTables::FactorRange> factorRange();

    void addTimesTable(const int number);
    void setMinFactor(const int min);
    void setMaxFactor(const int max);

private:
    Settings();
    ~Settings();

    QList<int> timesTables_;
    std::shared_ptr<FactorRange> factorRange_;
};

} // namespace TimesTables

#endif // OTTQ_20250831_1138_INCLUDE
