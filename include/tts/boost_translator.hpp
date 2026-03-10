#if !defined OTTQ_20260209_1318_INCLUDE && defined BOOST_TRANSLATOR
#  define OTTQ_20260209_1318_INCLUDE

#  include "abstract_translator.hpp"
#  include <boost/locale.hpp>

namespace Tts {

class Translator : public AbstractTranslator
{
public:
    Translator();

    std::string filePath() override;
    Tts::LocaleDescriptor localeDescriptor() override;
    Tts::Locale locale() override;
    std::string
    translate(const boost::locale::basic_message<char> &sourceText) override;
    bool load(const std::string &filePath) override;

private:
    boost::locale::generator generator_;
    std::locale locale_;
    std::string localeName_;
};

} // namespace Tts

#endif // OTTQ_20260209_1318_INCLUDE
