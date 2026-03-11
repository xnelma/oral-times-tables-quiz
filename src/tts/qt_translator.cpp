#if defined QT_TRANSLATOR // Needed for the linter.
#  include "qt_translator.hpp"
#  include "locale_descriptor.hpp"
#  include <QFile>
#  include <sstream>

Tts::Translator::Translator(QObject *parent) : translator_(parent) { }

std::string Tts::Translator::filePath() const
{
    return translator_.filePath().toStdString();
}

auto Tts::Translator::localeDescriptor() const -> LocaleDescriptor
{
    return Tts::LocaleDescriptor::fromResourcePath(filePath());
}

std::string Tts::Translator::translate(const std::string &sourceText) const
{
    return translator_.translate(TRANSLATION_DOMAIN, sourceText.c_str())
        .toStdString();
}

bool Tts::Translator::load(const std::string &filePath)
{
    QString qFilePath = QString::fromStdString(filePath);
    if (!QFile(qFilePath).exists()) {
        std::stringstream ss;
        ss << "Resource path \"" << filePath << "\" does not exist.";
        throw std::invalid_argument(ss.str());
    }

    return translator_.load(qFilePath);
}

#endif
