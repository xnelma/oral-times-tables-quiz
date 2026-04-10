#ifndef OTTQ_20260106_2039_INCLUDE
#define OTTQ_20260106_2039_INCLUDE

#include "locale_descriptor.hpp"
#if defined BOOST_TRANSLATOR
#  include <boost/locale.hpp>
#endif

namespace Tts {

class AbstractTranslator
{
public:
    AbstractTranslator() { }
    AbstractTranslator(AbstractTranslator const &) = default;
    AbstractTranslator(AbstractTranslator &&) noexcept = default;
    virtual ~AbstractTranslator() = default;

    AbstractTranslator &operator=(AbstractTranslator const &) = default;
    AbstractTranslator &operator=(AbstractTranslator &&) noexcept = default;

    virtual std::string filePath() const = 0;
    virtual Tts::LocaleDescriptor localeDescriptor() const = 0;
    Tts::Locale locale() const
    {
        auto ld = localeDescriptor();
        return Tts::Locale(ld.language, ld.territory);
    }
    // The translation libraries (so far) used have return values for the
    // translations, therefore also use a return value instead of a non-const
    // parameter.
#if defined BOOST_TRANSLATOR
    virtual std::string
    translate(const boost::locale::basic_message<char> &sourceText) const = 0;
#else
    virtual std::string translate(const std::string &sourceText) const = 0;
#endif
    virtual bool load(const std::string &filePath) = 0;
};

} // namespace Tts

#endif // OTTQ_20250106_2039_INCLUDE
