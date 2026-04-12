#if !defined OTTQ_20260410_1022_INCLUDE && defined BOOST_TRANSLATOR
#  define OTTQ_20260410_1022_INCLUDE

#  include <locale>
#  include <string>
#  include <boost/locale.hpp>

namespace Tts {

typedef std::locale BaseType;

enum Language {
    AnyLanguage, // ""
    C, // "c"
    German, // "de"
    English, // "en"
    French, // "fr"
    Italian // "it"
};

enum Territory {
    AnyTerritory, // ""
    Germany, // "DE"
    UnitedStates, // "US"
    UnitedKingdom, // "UK"
    France, // "FR"
    Italy // "IT"
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
            language_ = Tts::C;
            territory_ = Tts::AnyTerritory;
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
            return Tts::AnyLanguage;
        else if (languageCode == "c")
            return Tts::C;
        else if (languageCode == "de")
            return Tts::German;
        else if (languageCode == "en")
            return Tts::English;
        else if (languageCode == "fr")
            return Tts::French;
        else if (languageCode == "it")
            return Tts::Italian;
        else
            throw std::invalid_argument("Invalid language code \'"
                                        + languageCode + "\'");
        return Tts::C;
    }

    static Territory territory(const std::string &territoryCode)
    {
        if (territoryCode == "")
            return Tts::AnyTerritory;
        else if (territoryCode == "DE")
            return Tts::Germany;
        else if (territoryCode == "US")
            return Tts::UnitedStates;
        else if (territoryCode == "UK")
            return Tts::UnitedKingdom;
        else if (territoryCode == "FR")
            return Tts::France;
        else if (territoryCode == "IT")
            return Tts::Italy;
        else
            throw std::invalid_argument("Invalid territory code \'"
                                        + territoryCode + "\'");
        return Tts::AnyTerritory;
    }

    static std::string languageName(const Tts::Language &l)
    {
        switch (l) {
        case Tts::AnyLanguage:
            return "";
        case Tts::C:
            return "c";
        case Tts::German:
            return "de";
        case Tts::English:
            return "en";
        case Tts::French:
            return "fr";
        case Tts::Italian:
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
        case Tts::AnyTerritory:
            return "";
        case Tts::Germany:
            return "DE";
        case Tts::UnitedStates:
            return "US";
        case Tts::UnitedKingdom:
            return "UK";
        case Tts::France:
            return "FR";
        case Tts::Italy:
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
        if (l == Tts::C) {
            std::locale::global(std::locale::classic());
            return;
        }

        std::string name = Locale::languageName(l);
        if (t != Tts::AnyTerritory)
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
