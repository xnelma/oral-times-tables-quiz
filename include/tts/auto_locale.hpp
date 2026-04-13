#ifndef OTTQ_20260313_1231_INCLUDE
#define OTTQ_20260313_1231_INCLUDE

#if defined QT_TRANSLATOR
#  include "qt_locale.hpp"
#elif defined BOOST_TRANSLATOR
#  include "boost_locale.hpp"
#endif
#include "auto_locale_descriptor.hpp"

namespace Tts {

template <ExtendsResources TTranslationResources = Tts::TranslationResources>
struct AutoLocale
{
public:
    AutoLocale() { }

    Language::Code language()
    {
        descriptor_.update();
        return descriptor_.language;
    }

    Territory::Code territory()
    {
        descriptor_.update();
        return descriptor_.territory;
    }

    std::string name()
    {
        descriptor_.update();
        return Tts::Locale(descriptor_.language, descriptor_.territory).name();
    }

    explicit operator Locale::BaseType()
    {
        descriptor_.update();
        auto l = Tts::Locale(descriptor_.language, descriptor_.territory);
        return static_cast<Locale::BaseType>(l);
    }

private:
    Tts::AutoLocaleDescriptor<TTranslationResources> descriptor_;
};

} // namespace Tts

#endif // OTTQ_20260313_1231_INCLUDE
