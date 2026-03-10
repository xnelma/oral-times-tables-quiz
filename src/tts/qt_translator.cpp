#if defined QT_TRANSLATOR // Needed for the linter.
#  include "qt_translator.hpp"
#  include "locale_descriptor.hpp"
#  include <QFile>

Tts::Translator::Translator(QObject *parent) : translator_(parent) { }

std::string Tts::Translator::filePath()
{
    return translator_.filePath().toStdString();
}

auto Tts::Translator::localeDescriptor() -> LocaleDescriptor
{
    return Tts::LocaleDescriptor::fromResourcePath(filePath());
}

Tts::Locale Tts::Translator::locale()
{
    auto ld = localeDescriptor();
    return Tts::Locale(ld.language, ld.territory);
}

std::string Tts::Translator::translate(const std::string &sourceText)
{
    return translator_.translate(TRANSLATION_DOMAIN, sourceText.c_str())
        .toStdString();
}

bool Tts::Translator::load(const std::string &filePath)
{
    QString qFilePath = QString::fromStdString(filePath);
    if (!QFile(qFilePath).exists())
        throw std::invalid_argument(
            std::format("Resource path \"{}\" does not exist.", filePath));

    return translator_.load(qFilePath);
}

#endif
