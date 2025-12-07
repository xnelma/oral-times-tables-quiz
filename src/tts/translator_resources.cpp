#include "translator_resources.hpp"
#include <QFile>
#include <QDirIterator>

Tts::ResourceMap &Tts::Translator::resources()
{
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
