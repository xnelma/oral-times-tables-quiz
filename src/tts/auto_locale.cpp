#include "auto_locale.hpp"
#include "translator_resources.hpp"
#include <QFile>
#include <QDirIterator>

QLocale Tts::autoLocale(const QString qmSearchDir)
{
    // Use default constructor to allow setting a different 'system' locale,
    // for example for unit testing.
    QLocale sysLocale;

    std::optional<QLocale> fallbackLocale;

    for (auto resource : Tts::Translator::resources().keys()) {
        QLocale resourceLocale(resource.language, resource.territory);
        // TODO could I instead directly use the LocaleDescriptor?

        if (resourceLocale.name() == sysLocale.name())
            return sysLocale;

        if (!fallbackLocale.has_value())
            fallbackLocale = resourceLocale;

        resolveFallbackLocale(sysLocale, resourceLocale, *fallbackLocale);
    }

    return fallbackLocale.value_or(QLocale::c());
    // default_value shouldn't ever happen because unless no translation
    // resource is provided, the fallback was set to at least the locale of the
    // first translation resource in the list.
}

static void Tts::resolveFallbackLocale(const QLocale system,
                                       const QLocale resource,
                                       QLocale &fallback)
{
    bool fallbackIsInSystemLanguage = fallback.language() == system.language();
    bool fallbackIsInEnglish = fallback.language() == QLocale::English;

    bool reIsInSystemLanguage = resource.language() == system.language();
    bool reIsInEnglish = resource.language() == QLocale::English;
    bool reIsInSystemTerritory = resource.territory() == system.territory();

    if (fallbackIsInSystemLanguage)
        return;
    if (reIsInSystemLanguage // Best would be system language, other territory.
        || (reIsInEnglish // Otherwise use English:
            && (reIsInSystemTerritory // prefer the one item "en_SYS" in list,
                || !fallbackIsInEnglish))) { // else take first "en" in list.
        fallback = resource;
    }

    // FIXME The expected behavior for a resource without territory is that the
    // device territory is used!
}
