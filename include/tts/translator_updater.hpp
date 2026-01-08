#ifndef OTTQ_20250829_1807_INCLUDE
#define OTTQ_20250829_1807_INCLUDE

#include "abstract_tts_settings.hpp"
#include "locale_descriptor.hpp"
#include "abstract_translator.hpp"
#include <QLocale>

namespace Tts {

namespace TranslatorUpdater {

// TODO move to translator class
LocaleDescriptor localeDescriptor(Tts::AbstractTranslator &translator);
QLocale locale(Tts::AbstractTranslator &translator);

bool updateLocaleKey(LocaleDescriptor &localeKey,
                     Tts::AbstractSettings &settings);
void update(Tts::AbstractTranslator &translator,
            const LocaleDescriptor &updatedLocaleKey);

} // namespace TranslatorUpdater

} // namespace Tts

#endif // OTTQ_20250829_1807_INCLUDE
