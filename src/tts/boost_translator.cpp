#include "boost_translator.hpp"

#include <boost/locale.hpp>

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
