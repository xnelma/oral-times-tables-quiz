#if !defined OTTQ_20260410_1022_INCLUDE && defined BOOST_TRANSLATOR
#  define OTTQ_20260410_1022_INCLUDE

#  include "boost_language.hpp"
#  include "boost_territory.hpp"
#  include <locale>
#  include <string>
#  include <boost/locale.hpp>

namespace Tts {

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
            language_ = Language::fromString(l);
            territory_ = Territory::fromString(t);
        } else {
            language_ = Language::c;
            territory_ = Territory::ANY;
        }
    }

    explicit Locale(const Language::Code &l, const Territory::Code &t)
        : language_(l), territory_(t)
    {
    }

    Language::Code language() const { return language_; }
    Territory::Code territory() const { return territory_; }

    std::string name() const
    {
        std::string languageName = Language::toString(language_);
        if (languageName.empty())
            return "";
        std::string territoryName = Territory::toString(territory_);
        if (territoryName.empty())
            return languageName;

        return languageName + "_" + territoryName;
    }

    static void setDefault(const Language::Code &l, const Territory::Code &t)
    {
        if (l == Language::c) {
            std::locale::global(std::locale::classic());
            return;
        }

        std::string name = Language::toString(l);
        if (t != Territory::ANY)
            name += "_" + Territory::toString(t);

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
    Language::Code language_;
    Territory::Code territory_;
};

} // namespace Tts

#endif // OTTQ_20260410_1022_INCLUDE
