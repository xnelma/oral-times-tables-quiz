#ifndef SETTINGS_BACKEND_HPP
#define SETTINGS_BACKEND_HPP

#include "tts_language_settings.hpp"
#include "tts_rate_settings.hpp"
#include <QObject>
#include <qqml.h>
#include <QStringList>

class SettingsBackend : public QObject
{
    Q_OBJECT
    // clang-format off
    Q_PROPERTY(QStringList languages
               READ languages
               NOTIFY languagesChanged
               FINAL)
    Q_PROPERTY(int languageIndex
               READ languageIndex
               WRITE setLanguageIndex
               NOTIFY languageIndexChanged
               FINAL)
    Q_PROPERTY(bool useAutoTtsLanguage
               READ useAutoTtsLanguage
               WRITE setUseAutoTtsLanguage
               NOTIFY useAutoTtsLanguageChanged
               FINAL)
    Q_PROPERTY(QString autoLocaleName
               READ autoLocaleName
               NOTIFY autoLocaleNameChanged
               FINAL)
    Q_PROPERTY(double voiceRate
               READ voiceRate
               WRITE setVoiceRate
               NOTIFY voiceRateChanged
               FINAL)
    // clang-format on
    QML_ELEMENT

public:
    explicit SettingsBackend(QObject *parent = nullptr);

    QStringList languages();
    int languageIndex();
    bool useAutoTtsLanguage();
    QString autoLocaleName();
    double voiceRate();

    void setLanguageIndex(const int index);
    void setUseAutoTtsLanguage(const bool useAutoTtsLanguage);
    void setVoiceRate(const double rate);

signals:
    void languagesChanged();
    void languageIndexChanged();
    void useAutoTtsLanguageChanged();
    void autoLocaleNameChanged();
    void voiceRateChanged();

private:
    Tts::LanguageSettings languageSettings_;
    Tts::VoiceRateSettings voiceRateSettings_;
};

#endif // SETTINGS_BACKEND_HPP
