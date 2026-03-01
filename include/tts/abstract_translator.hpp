#ifndef OTTQ_20260106_2039_INCLUDE
#define OTTQ_20260106_2039_INCLUDE

#include "locale_descriptor.hpp"
#include <QString>
#include <QLocale>
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

    virtual std::string filePath() = 0;
    virtual Tts::LocaleDescriptor localeDescriptor() = 0;
    virtual QLocale locale() = 0;
    // The translation libraries (so far) used have return values for the
    // translations, therefore also use a return value instead of a non-const
    // parameter.
#if defined BOOST_TRANSLATOR
    virtual std::string
    translate(const boost::locale::basic_message<char> &sourceText) = 0;
#else
    virtual std::string translate(const std::string &sourceText) = 0;
#endif
    virtual bool load(const QString &filePath) = 0;
};

} // namespace Tts

#endif // OTTQ_20250106_2039_INCLUDE
