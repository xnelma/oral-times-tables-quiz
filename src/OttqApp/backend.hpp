#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <qqml.h>

class Backend : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    // TODO QML_SINGLETON or signals?

public:
    explicit Backend(QObject *parent = nullptr);
};

#endif // BACKEND_H
