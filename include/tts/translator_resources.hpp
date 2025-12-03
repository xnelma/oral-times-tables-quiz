#ifndef OTTQ_20251202_1917_INCLUDE
#define OTTQ_20251202_1917_INCLUDE

#include "locale_descriptor.hpp"
#include <QMap>

// TODO should even for subdirectories the top namespace be OTTQ?

namespace Tts {

// TODO or maybe a class, maybe even inheriting QTranslator?
namespace Translator {

typedef QMap<Tts::LocaleDescriptor, QString> ResourceMap;

extern ResourceMap resources();

} // namespace Translator

} // namespace Tts

#endif // OTTQ_20251202_1917_INCLUDE
