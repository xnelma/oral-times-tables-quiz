#ifndef OTTQ_20250925_2204_INCLUDE
#define OTTQ_20250925_2204_INCLUDE

#include "timestables/factor_range.hpp"
#include <QObject>
#include <qqml.h>
#include <memory>

struct FactorRange
{
    Q_GADGET
    Q_PROPERTY(int first READ first WRITE setFirst FINAL)
    Q_PROPERTY(int second READ second WRITE setSecond FINAL)
    QML_ANONYMOUS

public:
    FactorRange();
    FactorRange(std::shared_ptr<TimesTables::FactorRange> fr);

    int first() const;
    int second() const;
    std::shared_ptr<TimesTables::FactorRange> get() const;

    void setFirst(const int first) const;
    void setSecond(const int second) const;

    bool operator==(const FactorRange &fr);

private:
    std::shared_ptr<TimesTables::FactorRange> factorRange_;
};

#endif // OTTQ_20250925_2204_INCLUDE
