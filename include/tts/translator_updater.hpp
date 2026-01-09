#ifndef OTTQ_20250829_1807_INCLUDE
#define OTTQ_20250829_1807_INCLUDE

#include "abstract_tts_settings.hpp"
#include "locale_descriptor.hpp"
#include "abstract_translator.hpp"

namespace Tts {

namespace TranslatorUpdater {

bool updateLocaleKey(LocaleDescriptor &localeKey,
                     Tts::AbstractSettings &settings);
void update(Tts::AbstractTranslator &translator,
            Tts::AbstractSettings &settings);

} // namespace TranslatorUpdater

} // namespace Tts

#endif // OTTQ_20250829_1807_INCLUDE
