#ifndef OTTQ_20251202_1917_INCLUDE
#define OTTQ_20251202_1917_INCLUDE

#include "locale_descriptor.hpp"
#include <QStringList>
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
typedef std::pair<Tts::LocaleDescriptor, QString> ResourcePair;

// Use a struct instead of a namespace to be able to use it as type in
// templates. Then it can be replaced for testing.
struct TranslationResources
{
    static ResourceMap &get();
    static QStringList getLanguageNames();
    static long index(const Tts::LocaleDescriptor &key);

private:
    TranslationResources() { }
};

} // namespace Tts

#endif // OTTQ_20251202_1917_INCLUDE
