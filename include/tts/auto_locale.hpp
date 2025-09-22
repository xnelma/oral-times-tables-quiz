#ifndef AUTO_LOCALE_HPP
#define AUTO_LOCALE_HPP

#include "locale_descriptor.hpp"
#include <QLocale>
#include <QRegularExpression>

namespace Tts {

QLocale autoLocale();

static void resolveFallbackLocale(QLocale system, QLocale resource,
                                  QLocale &fallback);

// Path to generated translation resources.
const QString qmDirPath = ":/qt/qml/OttqApp/i18n/";
const QString qmFilePath = qmDirPath + "qml_%1.qm";

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

#endif // AUTO_LOCALE_HPP
