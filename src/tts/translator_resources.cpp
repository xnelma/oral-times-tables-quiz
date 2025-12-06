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
        auto file = QFile(dir);
        // TODO maybe split the directory string instead of parsing over QFile?

        auto descriptor = LocaleDescriptor::fromFileName(file.fileName());

        resources.insert({ descriptor, dir });
    }

    return resources;
}
