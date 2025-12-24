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
    LanguageName(const Tts::LocaleDescriptor &ld)
    {
        QLocale l(ld.language, ld.territory);
        language_ = l.nativeLanguageName();
        territory_ = l.nativeTerritoryName();
    }

    QString language() { return language_; }
    QString territory() { return territory_; }

private:
    QString language_;
    QString territory_;
};

#endif // OTTQ_20250915_1552_INCLUDE
