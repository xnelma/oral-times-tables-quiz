#ifndef OTTQ_20250829_1807_INCLUDE
#define OTTQ_20250829_1807_INCLUDE

#include "abstract_tts_settings.hpp"
#include "locale_descriptor.hpp"
#include <QLocale>
#include <QTranslator>

namespace Tts {

namespace TranslatorUpdater {

// TODO move to translator class
LocaleDescriptor localeDescriptor(const QTranslator &translator);
QLocale locale(const QTranslator &translator);

bool updateLocaleKey(LocaleDescriptor &localeKey,
                     Tts::AbstractSettings &settings);
void update(QTranslator &translator, const LocaleDescriptor &updatedLocaleKey);

} // namespace TranslatorUpdater

} // namespace Tts

#endif // OTTQ_20250829_1807_INCLUDE
