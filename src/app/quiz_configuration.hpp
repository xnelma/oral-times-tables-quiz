#ifndef SETUP_BACKEND_HPP
#define SETUP_BACKEND_HPP

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
    QML_SINGLETON
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
    std::shared_ptr<TimesTables::Settings> quizSettings_;

    FactorRange factorRange_;
};

#endif // SETUP_BACKEND_HPP
