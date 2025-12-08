#ifndef OTTQ_20250829_1806_INCLUDE
#define OTTQ_20250829_1806_INCLUDE

#include "locale_descriptor.hpp"
#include "quiz_translator.hpp"
#include <QLocale>
#include <QRegularExpression>
#include <QFile>
#include <QDirIterator>

namespace Tts {

static void resolveFallbackLocale(const Tts::LocaleDescriptor system,
                                  const Tts::LocaleDescriptor resource,
                                  Tts::LocaleDescriptor &fallback);

template <typename T>
concept ExtendsTranslator = std::is_base_of_v<Tts::QuizTranslator, T>; // C++20

template <ExtendsTranslator T = Tts::QuizTranslator>
inline auto autoLocale() -> LocaleDescriptor
{
    // Init with default constructor for QLocale instead of QLocale::system()
    // to allow setting a different 'system' locale by setting a default locale,
    // for example for unit testing.
    Tts::LocaleDescriptor system = Tts::LocaleDescriptor(QLocale());

    std::optional<Tts::LocaleDescriptor> fallback;

    static const Tts::ResourceMap resources = T::resources();
    for (Tts::ResourcePair r : resources) {
        Tts::LocaleDescriptor resource = r.first;

        if (resource == system)
            return system;

        if (!fallback.has_value())
            fallback = resource;

        resolveFallbackLocale(system, resource, *fallback);
    }

    return fallback.value_or(Tts::LocaleDescriptor());
    // default_value shouldn't ever happen because unless no translation
    // resource is provided, the fallback was set to at least the locale of the
    // first translation resource in the list.
}

static void resolveFallbackLocale(const Tts::LocaleDescriptor system,
                                  const Tts::LocaleDescriptor resource,
                                  Tts::LocaleDescriptor &fallback)
{
    bool fallbackIsInSystemLanguage = fallback.language == system.language;
    bool fallbackIsInEnglish = fallback.language == QLocale::English;

    bool resourceIsInSysLang = resource.language == system.language;
    bool resourceIsInEnglish = resource.language == QLocale::English;
    bool resourceIsInSysTerrit = resource.territory == system.territory;

    if (fallbackIsInSystemLanguage)
        return;
    if (resourceIsInSysLang // Best would be system language, other territory.
        || (resourceIsInEnglish // Otherwise use English:
            && (resourceIsInSysTerrit // prefer the one item "en_SYS" in list,
                || !fallbackIsInEnglish))) { // else take first "en" in list.
        fallback = resource;
    }

    // FIXME The expected behavior for a resource without territory is that the
    // device territory is used!
}

} // namespace Tts

#endif // OTTQ_20250829_1806_INCLUDE
