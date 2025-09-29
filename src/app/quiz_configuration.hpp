#ifndef OTTQ_20250830_2112_INCLUDE
#define OTTQ_20250830_2112_INCLUDE

#include "timestables/quiz_settings.hpp"
#include "factor_range.hpp"
#include <QObject>
#include <qqml.h>
#include <memory>

class QuizConfiguration : public QObject
{
    Q_OBJECT
    // clang-format off
    Q_PROPERTY(QString timesTablesStr
               READ timesTablesStr
               NOTIFY timesTablesStrChanged
               FINAL)
    Q_PROPERTY(QList<int> timesTables
               READ timesTables
               NOTIFY timesTablesChanged
               FINAL)
    Q_PROPERTY(FactorRange factorRange
               READ factorRange
               WRITE setFactorRange
               NOTIFY factorRangeChanged
               FINAL)
    // clang-format on
    QML_ELEMENT

public:
    explicit QuizConfiguration(QObject *parent = nullptr);

    Q_INVOKABLE void addTimesTable(const int number);

    QString timesTablesStr();
    QList<int> timesTables();
    FactorRange factorRange() const;

    void setFactorRange(const FactorRange &fr);

signals:
    void timesTablesStrChanged();
    void timesTablesChanged();
    void factorRangeChanged();

private:
    FactorRange factorRange_;
};

#endif // OTTQ_20250830_2112_INCLUDE
