#include "translation_resources.hpp"
#include <QFile>
#include <QDirIterator>
#include <algorithm>
#include <iterator>

Tts::ResourceMap &Tts::TranslationResources::get()
{
    // The translation resource list cannot change without an app update.
    static ResourceMap resources;

    if (resources.size() > 0)
        return resources;

    // ":" is the base path for Qt Resource files.
    QDirIterator it(":", { "*.qm" }, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString dir = it.next();
        auto descriptor = LocaleDescriptor::fromResourcePath(dir);

        resources.insert({ descriptor, dir });
    }

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
