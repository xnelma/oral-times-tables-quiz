#ifndef SETUP_BACKEND_HPP
#define SETUP_BACKEND_HPP

#include "quiz_settings.hpp"
#include <QObject>
#include <qqml.h>

class SetupBackend : public QObject
{
    Q_OBJECT
    // clang-format off
    Q_PROPERTY(QString timesTableNumbers
        READ timesTableNumbers
        NOTIFY timesTablesChanged)
    Q_PROPERTY(int minFactor
        READ minFactor
        WRITE setMinFactor
        NOTIFY minFactorChanged)
    Q_PROPERTY(int maxFactor
        READ maxFactor
        WRITE setMaxFactor
        NOTIFY maxFactorChanged)
    // clang-format on
    QML_ELEMENT

public:
    explicit SetupBackend(QObject *parent = nullptr);

    Q_INVOKABLE void addTimesTable(const int number);

    QString timesTableNumbers();
    int minFactor();
    int maxFactor();

    void setMinFactor(const int min);
    void setMaxFactor(const int max);

signals:
    void timesTablesChanged();
    void minFactorChanged();
    void maxFactorChanged();

private:
    TimesTables::Settings quizSettings_;
};

#endif // SETUP_BACKEND_HPP
