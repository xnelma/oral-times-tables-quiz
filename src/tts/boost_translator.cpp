#if defined BOOST_TRANSLATOR // Needed for the linter.
#  include "boost_translator.hpp"
#  include "boost_translation_dir.hpp"
#  include <filesystem>

Tts::Translator::Translator()
{
    generator_.add_messages_path(Tts::translationDir());
    generator_.add_messages_domain(TRANSLATION_DOMAIN);
}

std::string Tts::Translator::filePath() const
{
    if (localeName_.empty())
        return "";

    return "/" + localeName_ + ".po";
}

auto Tts::Translator::localeDescriptor() const -> LocaleDescriptor
{
    auto path = filePath();
    if (path.empty())
        return Tts::LocaleDescriptor();

    return Tts::LocaleDescriptor::fromResourcePath(path);
}

std::string Tts::Translator::translate(
    const boost::locale::basic_message<char> &sourceText) const
{
    return sourceText.str(locale_);
}

bool Tts::Translator::load(const std::string &filePath)
{
    std::filesystem::path p = filePath;
    if (!std::filesystem::exists(p))
        return false;

    // The stem of the filename for a xgettext translation file is the locale
    // name; there is no prefix or suffix.
    localeName_ = p.stem().string();

    // Assume for now that the filename does not contain the encoding.
    assert(localeName_.find(".") == std::string::npos);

    locale_ = generator_(localeName_ + ".UTF-8");

    return true;
}

#endif
