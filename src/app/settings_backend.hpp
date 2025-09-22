#ifndef SETTINGS_BACKEND_HPP
#define SETTINGS_BACKEND_HPP

#include "tts/tts_language_settings.hpp"
#include "tts/tts_rate_settings.hpp"
#include "language_name.hpp"
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
    Q_PROPERTY(LanguageName autoLanguage
               READ autoLanguage
               NOTIFY autoLanguageChanged
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
    LanguageName autoLanguage();
    double voiceRate();

    void setLanguageIndex(const int index);
    void setUseAutoTtsLanguage(const bool useAutoTtsLanguage);
    void setVoiceRate(const double rate);

signals:
    void languagesChanged();
    void languageIndexChanged();
    void useAutoTtsLanguageChanged();
    void autoLanguageChanged();
    void voiceRateChanged();

private:
    Tts::LanguageSettings languageSettings_;
    Tts::VoiceRateSettings voiceRateSettings_;
};

#endif // SETTINGS_BACKEND_HPP
