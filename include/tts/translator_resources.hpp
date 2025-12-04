#ifndef OTTQ_20251202_1917_INCLUDE
#define OTTQ_20251202_1917_INCLUDE

#include "locale_descriptor.hpp"
#include <unordered_map>

template <>
struct std::hash<Tts::LocaleDescriptor>
{
    std::size_t operator()(const Tts::LocaleDescriptor &ld) const
    {
        return std::hash<int>()(ld.language)
            ^ std::hash<int>()(ld.territory << 1);
    }
};

// TODO should even for subdirectories the top namespace be OTTQ?

namespace Tts {

typedef std::unordered_map<Tts::LocaleDescriptor, QString> ResourceMap;

// TODO or maybe a class, maybe even inheriting QTranslator?
namespace Translator {

extern ResourceMap resources();

} // namespace Translator

} // namespace Tts

#endif // OTTQ_20251202_1917_INCLUDE
