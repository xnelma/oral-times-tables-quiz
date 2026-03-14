#ifndef OTTQ_20250915_1552_INCLUDE
#define OTTQ_20250915_1552_INCLUDE

#include <tts/locale_descriptor.hpp>
#include <QObject>
#include <qqml.h>
#include <QString>
#include <QLocale>

struct LanguageName
{
    Q_GADGET
    Q_PROPERTY(QString language READ language CONSTANT FINAL)
    Q_PROPERTY(QString territory READ territory CONSTANT FINAL)
    QML_ANONYMOUS

public:
    LanguageName() : language_(""), territory_("") { }
    // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
    LanguageName(const QString &language, const QString &territory)
        : language_(language), territory_(territory)
    {
    }

    QString language() { return language_; }
    QString territory() { return territory_; }

private:
    QString language_;
    QString territory_;
};

#endif // OTTQ_20250915_1552_INCLUDE
