#if !defined OTTQ_20260413_1554_INCLUDE && defined BOOST_TRANSLATOR
#  define OTTQ_20260413_1554_INCLUDE

#  include <string>
#  include <unordered_map>
#  include <stdexcept>

namespace Tts {
namespace Territory {

enum Code {
    ANY, // ""
    DE,
    US,
    UK,
    FR,
    IT
};

static Code fromString(const std::string &territoryCode)
{
    static const std::unordered_map<std::string, Code> dict = {
        { "", ANY },  { "DE", DE }, { "US", US },
        { "UK", UK }, { "FR", FR }, { "IT", IT }
    };

    try {
        return dict.at(territoryCode);
    } catch (const std::out_of_range &e) {
        throw std::invalid_argument("Invalid territory code \'" + territoryCode
                                    + "\'");
    }

    return ANY;
}

static std::string toString(const Code &territoryCode)
{
    static const std::unordered_map<Territory::Code, std::string> dict = {
        { ANY, "" },  { DE, "DE" }, { US, "US" },
        { UK, "UK" }, { FR, "FR" }, { IT, "IT" }
    };

    try {
        return dict.at(territoryCode);
    } catch (const std::out_of_range &e) {
        throw std::invalid_argument("Invalid territory type \'"
                                    + std::to_string(territoryCode) + "\'");
    }

    return "";
}

} // namespace Territory
} // namespace Tts

#endif // OTTQ_20260413_1554_INCLUDE