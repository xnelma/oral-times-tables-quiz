#ifndef SETTINGS_BACKEND_HPP
#define SETTINGS_BACKEND_HPP

#include "tts_language_settings.hpp"
#include <QObject>
#include <qqml.h>
#include <QStringList>

class SettingsBackend : public QObject
{
    Q_OBJECT
    // clang-format off
    Q_PROPERTY(QStringList languages READ languages NOTIFY languagesChanged)
    Q_PROPERTY(int languageIndex
               READ languageIndex
               WRITE setLanguageIndex
               NOTIFY languageIndexChanged)
    Q_PROPERTY(bool useAutoTtsLanguage
               READ useAutoTtsLanguage
               WRITE setUseAutoTtsLanguage
               NOTIFY useAutoTtsLanguageChanged)
    Q_PROPERTY(QString autoLocaleName
               READ autoLocaleName
               NOTIFY autoLocaleNameChanged)
    // clang-format on
    QML_ELEMENT

public:
    explicit SettingsBackend(QObject *parent = nullptr);

    QStringList languages();
    int languageIndex();
    bool useAutoTtsLanguage();
    QString autoLocaleName();

    void setLanguageIndex(const int index);
    void setUseAutoTtsLanguage(const bool useAutoTtsLanguage);

signals:
    void languagesChanged();
    void languageIndexChanged();
    void useAutoTtsLanguageChanged();
    void autoLocaleNameChanged();

private:
    Tts::LanguageSettings languageSettings_;
};

#endif // SETTINGS_BACKEND_HPP
