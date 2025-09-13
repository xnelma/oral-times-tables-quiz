#ifndef SETUP_BACKEND_HPP
#define SETUP_BACKEND_HPP

#include "quiz_settings.hpp"
#include <QObject>
#include <qqml.h>

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
    Q_PROPERTY(int minFactor
               READ minFactor
               WRITE setMinFactor
               NOTIFY minFactorChanged
               FINAL)
    Q_PROPERTY(int maxFactor
               READ maxFactor
               WRITE setMaxFactor
               NOTIFY maxFactorChanged
               FINAL)
    // clang-format on
    QML_SINGLETON
    QML_ELEMENT

public:
    explicit QuizConfiguration(QObject *parent = nullptr);

    Q_INVOKABLE void addTimesTable(const int number);

    QString timesTablesStr();
    QList<int> timesTables();
    int minFactor();
    int maxFactor();

    void setMinFactor(const int min);
    void setMaxFactor(const int max);

signals:
    void timesTablesStrChanged();
    void timesTablesChanged();
    void minFactorChanged();
    void maxFactorChanged();

private:
    TimesTables::Settings quizSettings_;
};

#endif // SETUP_BACKEND_HPP
