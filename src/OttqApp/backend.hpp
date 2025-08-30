#ifndef BACKEND_HPP
#define BACKEND_HPP

#include <QObject>
#include <qqml.h>

class Backend : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

public:
    explicit Backend(QObject *parent = nullptr);
};

#endif // BACKEND_HPP
