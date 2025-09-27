#ifndef OTTQ_20250925_2204_INCLUDE
#define OTTQ_20250925_2204_INCLUDE

#include "timestables/quiz_settings.hpp"
#include <QObject>
#include <qqml.h>
#include <memory>

struct FactorRange
{
    Q_GADGET
    Q_PROPERTY(int min READ min WRITE setMin FINAL)
    Q_PROPERTY(int max READ max WRITE setMax FINAL)
    QML_ANONYMOUS

public:
    FactorRange();
    FactorRange(std::shared_ptr<TimesTables::Settings> quizSettings);

    int min() const;
    int max() const;

    void setMin(const int min) const;
    void setMax(const int max) const;

    bool operator==(const FactorRange &fr);

private:
    std::shared_ptr<TimesTables::Settings> quizSettings_;
};

#endif // OTTQ_20250925_2204_INCLUDE
