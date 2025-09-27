#ifndef OTTQ_20250811_1825_INCLUDE
#define OTTQ_20250811_1825_INCLUDE

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

#endif // OTTQ_20250811_1825_INCLUDE
