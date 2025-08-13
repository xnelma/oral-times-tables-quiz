#include "backend.hpp"

#include <QCoreApplication>
#include <QLocale>
#include <QtLogging>

#include "placeholder.hpp"

Backend::Backend(QObject *parent) : QObject{ parent }
{
    bool ok = translator_.load(QString(":/qt/qml/OttqApp/i18n/qml_de.qm"));
    // TODO error handling instead of logging
    if (!ok)
        qWarning("Couldn't load translation file");
}

QString Backend::getQuestion()
{
    Placeholder p;
    return translator_.translate("Main", "%1 times %2").arg(p.a).arg(p.b);
}
