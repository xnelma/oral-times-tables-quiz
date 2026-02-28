#include "boost_translator.hpp"
#include <filesystem>

Tts::Translator::Translator()
{
    generator_.add_messages_path(TRANSLATION_DIR);
    generator_.add_messages_domain(TRANSLATION_DOMAIN);
}

QString Tts::Translator::filePath()
{
    if (localeName_.empty())
        return "";

    return QString::fromStdString(std::vformat(
        TRANSLATION_DIR "/{}.po", std::make_format_args(localeName_)));
}

auto Tts::Translator::localeDescriptor() -> LocaleDescriptor
{
    auto path = filePath();
    if (path.isEmpty())
        return Tts::LocaleDescriptor();

    return Tts::LocaleDescriptor::fromResourcePath(path.toStdString());
}

QLocale Tts::Translator::locale()
{
    // TODO If I am not using QLocale, but std::locale, how would I provide
    // the locale names? namespace constants?
    auto ld = localeDescriptor();
    return QLocale(ld.language, ld.territory); // TODO
}

std::string
Tts::Translator::translate(const boost::locale::basic_message<char> &sourceText)
{
    return sourceText.str(locale_);
}

bool Tts::Translator::load(const QString &filename)
// TODO rename to filePath
{
    std::filesystem::path p = filename.toStdString();
    if (!std::filesystem::exists(p))
        return false;

    // The stem of the filename for a xgettext translation file is the locale
    // name; there is no prefix or suffix.
    localeName_ = p.stem().string();

    // Assume for now that the filename does not contain the encoding.
    assert(localeName_.find(".") == std::string::npos);

    locale_ = generator_(
        std::vformat("{}.UTF-8", std::make_format_args(localeName_)));

    return true;
}
