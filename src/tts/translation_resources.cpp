#include "translation_resources.hpp"
#if defined QT_TRANSLATOR
#  include <QDirIterator>
#elif defined BOOST_TRANSLATOR
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
        QString dir = it.next();
        auto descriptor = LocaleDescriptor::fromResourcePath(dir.toStdString());

        resources.insert({ descriptor, dir });
    }
#elif defined BOOST_TRANSLATOR
    std::ranges::for_each(
        std::filesystem::recursive_directory_iterator(TRANSLATION_DIR),
        [](const auto &dirEntry) {
            auto filename = dirEntry.path().filename().string();
            if (filename.ends_with(".po") /* C++20 */) {
                auto descriptor = LocaleDescriptor::fromFileName(filename);
                resources.insert(
                    { descriptor, QString::fromStdString(filename) });
            }
        });
#endif

    return resources;
}

QStringList Tts::TranslationResources::getLanguageNames()
{
    static QStringList languageNames;
    if (languageNames.size() > 0)
        return languageNames;

    // C++20
    std::ranges::transform(
        TranslationResources::get(),
        std::back_inserter(languageNames),
        [](const ResourcePair &key) -> QString {
            LocaleDescriptor ld = key.first;
            return QLocale(ld.language, ld.territory).nativeLanguageName();
        });

    return languageNames;
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
