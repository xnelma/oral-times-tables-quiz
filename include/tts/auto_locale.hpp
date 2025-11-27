#ifndef OTTQ_20250829_1806_INCLUDE
#define OTTQ_20250829_1806_INCLUDE

#include "locale_descriptor.hpp"
#include <QLocale>
#include <QRegularExpression>

namespace Tts {

// Search Qt Resources by default, but also allow setting the search directory.
// This is useful for unit testing, where Qt Resources might not be loaded.
// FIXME The parameter here does not make much sense. It should be a (static?)
// member of a class.
QLocale autoLocale(const QString qmSearchDir = ":");

QString resourcePath();

static void resolveFallbackLocale(QLocale system, QLocale resource,
                                  QLocale &fallback);

// Path to generated translation resources.
const QString qmDirPath = ":/qt/qml/OttqApp/i18n/";
const QString qmFilePath = qmDirPath + "qml_%1.qm";
// TODO if I do not use a fixed path but find it dynamically, I need to set
// the path to get the .qm file from in tts/quiz_translator.cpp dynamically,
// too. This would also be needed for unit testing.

// Regex for getting the locale name from a translation resource file name.
// File names could for example be qml_xx.qm or qml_xx_XX.qm, and more
// generally [prefix]xx.qm or [prefix]xx_XX.qm or with a third letter for
// language or region and allowing '-' as delimiter.
// This is an oversimplified assumption and requires that only language and
// maybe territory are specified when registering the translation resources.
// But it allows for changing the resource prefix of translation files.
const auto qmLocaleNameRegex =
    QRegularExpression("^.*([a-z]{2,3})([_-][A-Z]{2,3}){,1}.qm$");

} // namespace Tts

#endif // OTTQ_20250829_1806_INCLUDE
