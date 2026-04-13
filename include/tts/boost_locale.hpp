#if !defined OTTQ_20260410_1022_INCLUDE && defined BOOST_TRANSLATOR
#  define OTTQ_20260410_1022_INCLUDE

#  include <locale>
#  include <string>
#  include <unordered_map>
#  include <boost/locale.hpp>

namespace Tts {

enum Language {
    any, // ""
    c,
    de,
    en,
    fr,
    it
};

enum Territory {
    ANY, // ""
    DE,
    US,
    UK,
    FR,
    IT
};

struct Locale
{
public:
    typedef std::locale BaseType;

    Locale()
    {
        auto sys = std::locale();
        if (std::has_facet<boost::locale::info>(sys)) {
            auto l = std::use_facet<boost::locale::info>(sys).language();
            auto t = std::use_facet<boost::locale::info>(sys).country();
            language_ = language(l);
            territory_ = territory(t);
        } else {
            language_ = Tts::c;
            territory_ = Tts::ANY;
        }
    }

    explicit Locale(const Tts::Language &l, const Tts::Territory &t)
        : language_(l), territory_(t)
    {
    }

    Language language() const { return language_; }
    Territory territory() const { return territory_; }

    static Language language(const std::string &languageCode)
    {
        static const std::unordered_map<std::string, Language> dict = {
            { "", any },  { "c", c },   { "de", de },
            { "en", en }, { "fr", fr }, { "it", it }
        };

        try {
            return dict.at(languageCode);
        } catch (const std::out_of_range &e) {
            throw std::invalid_argument("Invalid language code \'"
                                        + languageCode + "\'");
        }

        return Tts::c;
    }

    static Territory territory(const std::string &territoryCode)
    {
        static const std::unordered_map<std::string, Territory> dict = {
            { "", ANY },  { "DE", DE }, { "US", US },
            { "UK", UK }, { "FR", FR }, { "IT", IT }
        };

        try {
            return dict.at(territoryCode);
        } catch (const std::out_of_range &e) {
            throw std::invalid_argument("Invalid territory code \'"
                                        + territoryCode + "\'");
        }

        return Tts::ANY;
    }

    static std::string languageName(const Tts::Language &l)
    {
        static std::unordered_map<Language, std::string> dict = {
            { any, "" },  { c, "c" },   { de, "de" },
            { en, "en" }, { fr, "fr" }, { it, "it" }
        };

        try {
            return dict.at(l);
        } catch (const std::out_of_range &e) {
            throw std::invalid_argument("Invalid language type \'"
                                        + std::to_string(l) + "\'");
        }

        return "c";
    }

    static std::string territoryName(const Tts::Territory &t)
    {
        static const std::unordered_map<Territory, std::string> dict = {
            { ANY, "" },  { DE, "DE" }, { US, "US" },
            { UK, "UK" }, { FR, "FR" }, { IT, "IT" }
        };

        try {
            return dict.at(t);
        } catch (const std::out_of_range &e) {
            throw std::invalid_argument("Invalid territory type \'"
                                        + std::to_string(t) + "\'");
        }

        return "";
    }

    std::string name() const
    {
        std::string languageName = Locale::languageName(language_);
        if (languageName.empty())
            return "";
        std::string territoryName = Locale::territoryName(territory_);
        if (territoryName.empty())
            return languageName;

        return languageName + "_" + territoryName;
    }

    static void setDefault(const Tts::Language &l, const Tts::Territory &t)
    {
        if (l == Tts::c) {
            std::locale::global(std::locale::classic());
            return;
        }

        std::string name = Locale::languageName(l);
        if (t != Tts::ANY)
            name += "_" + Locale::territoryName(t);

        boost::locale::generator gen;
        std::locale::global(gen(name + ".UTF-8"));
    }

    explicit operator BaseType() const
    {
        boost::locale::generator gen;
        std::locale l = gen(name() + ".UTF-8");
        return l;
    }

private:
    Tts::Language language_;
    Tts::Territory territory_;
};

} // namespace Tts

#endif // OTTQ_20260410_1022_INCLUDE
