#include "boost_translator.hpp"

Tts::Translator::Translator()
{
    generator_.add_messages_path(TRANSLATION_DIR);
    generator_.add_messages_domain(TRANSLATION_DOMAIN);
}

QString Tts::Translator::filePath()
{
    return ""; // TODO
}

auto Tts::Translator::localeDescriptor() -> LocaleDescriptor
{
    return Tts::LocaleDescriptor(); // TODO
}

QLocale Tts::Translator::locale()
{
    return QLocale(); // TODO
}

std::string
Tts::Translator::translate(const boost::locale::basic_message<char> &sourceText)
{
    return ""; // TODO
}

bool Tts::Translator::load(const QString &filename)
{
    return true; // TODO
}
