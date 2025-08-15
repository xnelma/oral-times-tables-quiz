#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <qqml.h>
#include <QSettings>
#include <QTranslator>

class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool setting READ setting WRITE setSetting NOTIFY settingChanged)
    QML_ELEMENT
    QML_SINGLETON

public:
    explicit Backend(QObject *parent = nullptr);

    Q_INVOKABLE QString getQuestion();

    bool setting();

    void setSetting(const bool &s);

signals:
    void settingChanged();

private:
    QTranslator translator_;
    QSettings settings_;

    bool setting_;
};

#endif // BACKEND_H
