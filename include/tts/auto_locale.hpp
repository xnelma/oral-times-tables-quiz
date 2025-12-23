#ifndef OTTQ_20250829_1806_INCLUDE
#define OTTQ_20250829_1806_INCLUDE

#include "locale_descriptor.hpp"
#include "translation_resources.hpp"
#include <QLocale>
#include <QRegularExpression>
#include <QFile>
#include <QDirIterator>
#include <exception>

namespace Tts {

template <typename T>
concept ExtendsResources = std::is_base_of_v<Tts::TranslationResources, T>;
// C++20

template <ExtendsResources TR = Tts::TranslationResources>
struct AutoLocale : public LocaleDescriptor
{
    AutoLocale() { set(); }

private:
    void set()
    {
        // Init with default constructor for QLocale instead of
        // QLocale::system() to allow setting a different 'system' locale by
        // setting a default locale, for example for unit testing.
        Tts::LocaleDescriptor system = Tts::LocaleDescriptor(QLocale());

        std::optional<Tts::LocaleDescriptor> fallback;

        // T::resources() is not saved in a static local variable on purpose:
        // it can change for unit tests.
        // It can already be static in T::resources() to avoid rebuilding the
        // list on every call.
        const Tts::ResourceMap resources = TR::get();

        // An empty translation resource list should not be possible. If the
        // translations are id-based, there is not even a default english
        // translation available, so allowing the c-locale as fallback would
        // not make sense.
        if (resources.size() == 0)
            throw std::invalid_argument("No translation resource files found.");

        for (Tts::ResourcePair r : resources) {
            Tts::LocaleDescriptor resource = r.first;

            if (resource == system) {
                language = system.language;
                territory = system.territory;
                return;
            }

            // The preferred fallback would be finding a translation resource
            // with a matching language. Of those translation resources, take
            // the first.
            if (!fallback.has_value() && resource.language == system.language)
                fallback = system;
        }

        // If there is no translation available for the system language, use the
        // first translation resource as 'automatic' tts locale.
        // It can still be changed manually anyways.
        if (!fallback.has_value())
            fallback = resources.begin()->first;

        language = fallback->language;
        territory = fallback->territory;
    }
};

} // namespace Tts

#endif // OTTQ_20250829_1806_INCLUDE
