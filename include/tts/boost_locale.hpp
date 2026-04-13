#if !defined OTTQ_20260410_1022_INCLUDE && defined BOOST_TRANSLATOR
#  define OTTQ_20260410_1022_INCLUDE

#  include <locale>
#  include <string>
#  include <boost/locale.hpp>

namespace Tts {

typedef std::locale BaseType;

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
        if (languageCode == "")
            return Tts::any;
        else if (languageCode == "c")
            return Tts::c;
        else if (languageCode == "de")
            return Tts::de;
        else if (languageCode == "en")
            return Tts::en;
        else if (languageCode == "fr")
            return Tts::fr;
        else if (languageCode == "it")
            return Tts::it;
        else
            throw std::invalid_argument("Invalid language code \'"
                                        + languageCode + "\'");
        return Tts::c;
    }

    static Territory territory(const std::string &territoryCode)
    {
        if (territoryCode == "")
            return Tts::ANY;
        else if (territoryCode == "DE")
            return Tts::DE;
        else if (territoryCode == "US")
            return Tts::US;
        else if (territoryCode == "UK")
            return Tts::UK;
        else if (territoryCode == "FR")
            return Tts::FR;
        else if (territoryCode == "IT")
            return Tts::IT;
        else
            throw std::invalid_argument("Invalid territory code \'"
                                        + territoryCode + "\'");
        return Tts::ANY;
    }

    static std::string languageName(const Tts::Language &l)
    {
        switch (l) {
        case Tts::any:
            return "";
        case Tts::c:
            return "c";
        case Tts::de:
            return "de";
        case Tts::en:
            return "en";
        case Tts::fr:
            return "fr";
        case Tts::it:
            return "it";
        default:
            throw std::invalid_argument("Invalid language type \'"
                                        + std::to_string(l) + "\'");
        }
        return "c";
    }

    static std::string territoryName(const Tts::Territory &t)
    {
        switch (t) {
        case Tts::ANY:
            return "";
        case Tts::DE:
            return "DE";
        case Tts::US:
            return "US";
        case Tts::UK:
            return "UK";
        case Tts::FR:
            return "FR";
        case Tts::IT:
            return "IT";
        default:
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
