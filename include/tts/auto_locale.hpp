#ifndef OTTQ_20260313_1231_INCLUDE
#define OTTQ_20260313_1231_INCLUDE

#include "qt_locale.hpp"
#include "auto_locale_descriptor.hpp"

namespace Tts {

template <ExtendsResources TTranslationResources = Tts::TranslationResources>
struct AutoLocale : private Tts::Locale
{
public:
    AutoLocale() { }

    Language language()
    {
        descriptor_.update();
        return descriptor_.language;
    }

    Territory territory()
    {
        descriptor_.update();
        return descriptor_.territory;
    }

    std::string name()
    {
        descriptor_.update();
        return QLocale(descriptor_.language, descriptor_.territory)
            .name()
            .toStdString();
    }

    explicit operator QLocale()
    {
        descriptor_.update();
        return QLocale(descriptor_.language, descriptor_.territory);
    }

private:
    Tts::AutoLocaleDescriptor<TTranslationResources> descriptor_;
};

} // namespace Tts

#endif // OTTQ_20260313_1231_INCLUDE
