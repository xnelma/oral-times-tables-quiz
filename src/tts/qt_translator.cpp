#if defined QT_TRANSLATOR // Needed for the linter.
#  include "qt_translator.hpp"
#  include "locale_descriptor.hpp"
#  include <QFile>

Tts::Translator::Translator(QObject *parent) : translator_(parent) { }

QString Tts::Translator::filePath()
{
    return translator_.filePath();
}

auto Tts::Translator::localeDescriptor() -> LocaleDescriptor
{
    return Tts::LocaleDescriptor::fromResourcePath(filePath().toStdString());
}

QLocale Tts::Translator::locale()
{
    auto ld = localeDescriptor();
    return QLocale(ld.language, ld.territory);
}

std::string Tts::Translator::translate(const std::string &sourceText)
{
    return translator_.translate(TRANSLATION_DOMAIN, sourceText.c_str())
        .toStdString();
}

bool Tts::Translator::load(const QString &filename)
{
    if (!QFile(filename).exists())
        throw std::invalid_argument(std::format(
            "Resource path \"{}\" does not exist.", filename.toStdString()));

    return translator_.load(filename);
}

#endif
