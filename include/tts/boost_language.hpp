#if !defined OTTQ_20260413_1551_INCLUDE && defined BOOST_TRANSLATOR
#  define OTTQ_20260413_1551_INCLUDE

#  include <string>
#  include <unordered_map>
#  include <stdexcept>

namespace Tts {
namespace Language {

enum Code {
    any, // ""
    c,
    de,
    en,
    fr,
    it
};

static Code fromString(const std::string &languageCode)
{
    static const std::unordered_map<std::string, Code> dict = {
        { "", any },  { "c", c },   { "de", de },
        { "en", en }, { "fr", fr }, { "it", it }
    };

    try {
        return dict.at(languageCode);
    } catch (const std::out_of_range &e) {
        throw std::invalid_argument("Invalid language code \'" + languageCode
                                    + "\'");
    }

    return c;
}

static std::string toString(const Language::Code &languageCode)
{
    static std::unordered_map<Code, std::string> dict = {
        { any, "" },  { c, "c" },   { de, "de" },
        { en, "en" }, { fr, "fr" }, { it, "it" }
    };

    try {
        return dict.at(languageCode);
    } catch (const std::out_of_range &e) {
        throw std::invalid_argument("Invalid language type \'"
                                    + std::to_string(languageCode) + "\'");
    }

    return "c";
}

} // namespace Language
} // namespace Tts

#endif // OTTQ_20260413_1551_INCLUDE