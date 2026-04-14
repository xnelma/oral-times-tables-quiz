#include "translation_resources.hpp"
#if defined QT_TRANSLATOR
#  include <QDirIterator>
#elif defined BOOST_TRANSLATOR
#  include "boost_translation_dir.hpp"
#  include <filesystem>
#endif
#include <algorithm>
#include <iterator>
#include <stdexcept>

Tts::ResourceMap &Tts::TranslationResources::get()
{
    // The translation resource list cannot change without an app update.
    static ResourceMap resources;

    if (resources.size() > 0)
        return resources;

#if defined QT_TRANSLATOR
    // ":" is the base path for Qt Resource files.
    QDirIterator it(":", { "*.qm" }, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        auto dirStr = it.next().toStdString();
        auto descriptor = LocaleDescriptor::fromResourcePath(dirStr);

        resources.insert({ descriptor, dirStr });
    }
#elif defined BOOST_TRANSLATOR
    std::ranges::for_each(
        std::filesystem::recursive_directory_iterator(Tts::translationDir()),
        [](const auto &dirEntry) {
            auto dir = dirEntry.path();
            auto dirStr = dir.string();
            if (dirStr.ends_with("." + std::string(TRANSLATION_FILE_ENDING))
                /* C++20 */) {
                auto descriptor =
                    LocaleDescriptor::fromFileName(dir.filename().string());
                resources.insert({ descriptor, dirStr });
            }
        });
#endif

    return resources;
}

std::vector<Tts::Locale> Tts::TranslationResources::getLocales()
{
    static std::vector<Tts::Locale> locales;
    if (locales.size() > 0)
        return locales;

    // C++20
    std::ranges::transform(TranslationResources::get(),
                           std::back_inserter(locales),
                           [](const ResourcePair &key) -> Tts::Locale {
                               LocaleDescriptor ld = key.first;
                               return Tts::Locale(ld.language, ld.territory);
                           });

    return locales;
}

long Tts::TranslationResources::index(const Tts::LocaleDescriptor &key)
{
    // Should not be static because of unit testing.
    const ResourceMap resources = TranslationResources::get();
    const ResourceMap::const_iterator itBegin = resources.begin();

    auto itKey = resources.find(key);

    // Return an invalid index if the key was not found, instead of finding
    // a fallback index (for a matching language but different territory).
    // The settings are set with the keys from the ResourceMap, so the key
    // should always have a match in the ResourceMap.
    // The translation resources could change with an app update and cause
    // a saved locale to become invalid. Since it is then invalid, the settings
    // should also not be secretely changed, and highlighting an item in the
    // list without saving to settings would lead to a different locale being
    // used in the quiz.
    if (itKey == resources.end())
        return -1;

    return std::distance(itBegin, itKey);
}

auto Tts::TranslationResources::locale(const long &index) -> LocaleDescriptor
{
    auto resources = TranslationResources::get();

    if (index < 0)
        throw std::invalid_argument("Index is smaller than 0.");
    if (index >= resources.size())
        throw std::invalid_argument("Index is larger than or equal to the"
                                    "resources size.");

    ResourceMap::iterator it = resources.begin();
    std::advance(it, index);

    return it->first;
}
