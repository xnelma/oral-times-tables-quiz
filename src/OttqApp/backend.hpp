#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <qqml.h>
#include <QTranslator>

class Backend : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

public:
    explicit Backend(QObject *parent = nullptr);

    Q_INVOKABLE QString getQuestion();

private:
    QTranslator translator_;
};

#endif // BACKEND_H
