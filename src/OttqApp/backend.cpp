#include "backend.hpp"

#include <QCoreApplication>
#include <QLocale>
#include <QtLogging>

#include "placeholder.hpp"

Backend::Backend(QObject *parent) : QObject{ parent }
{
    setting_ = settings_.value("setting", false) == true;
    emit settingChanged();

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

bool Backend::setting()
{
    return setting_;
}

void Backend::setSetting(const bool &s)
{
    setting_ = s;

    settings_.setValue("setting", setting_);

    emit settingChanged();
}
