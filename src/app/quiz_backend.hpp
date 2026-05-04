#ifndef OTTQ_20250829_1810_INCLUDE
#define OTTQ_20250829_1810_INCLUDE

#include "quiz_state_machine.hpp"
#include "tts/self_updating_translator.hpp"
#include "tts/tts_settings.hpp"
#include "timestables/quiz.hpp"
#include <QObject>
#include <qqml.h>
#include <QLocale>
#include <QString>
#include <QTextToSpeech>
#include <memory>

class QuizBackend : public QObject
{
    Q_OBJECT
    // clang-format off
    Q_PROPERTY(QString localeName
               READ localeName
               NOTIFY localeNameChanged
               FINAL)
    Q_PROPERTY(double voiceRate
               READ voiceRate
               NOTIFY voiceRateChanged
               FINAL)
    Q_PROPERTY(int numQuestionsRemaining
               READ numQuestionsRemaining
               NOTIFY numQuestionsRemainingChanged
               FINAL)
    Q_PROPERTY(QString state
               READ state
               NOTIFY stateChanged
               FINAL)
    // clang-format on
    QML_ELEMENT

public:
    explicit QuizBackend(QObject *parent = nullptr);

    QString state();
    QString localeName();
    double voiceRate();
    int numQuestionsRemaining();

    Q_INVOKABLE void startStateMachine();
    Q_INVOKABLE void stopStateMachine();

    Q_INVOKABLE void ttsReady();
    Q_INVOKABLE void ttsSpeaking();
    Q_INVOKABLE void ttsError();
    Q_INVOKABLE bool next();
    Q_INVOKABLE bool correct(const int answer);
    Q_INVOKABLE void quizCompleted();

    Q_INVOKABLE QString question();

signals:
    void localeNameChanged();
    void numQuestionsRemainingChanged();
    void questionChanged();
    void stateChanged();
    void setup();
    void firstQuestion();
    void voiceRateChanged();

private:
    void setupStateMachine();

    std::unique_ptr<QuizStateMachine> machine_;
    TimesTables::Quiz quiz_;

    // The class outlives QuizView being on top of the stack, so the locale
    // can be updated in the settings and would need to be applied when
    // returning to the view. This would be handled inside the translator.
    Tts::SelfUpdatingTranslator<Tts::Translator> translator_;
    Tts::Settings settings_;
    std::string questionBase_;
};

#endif // OTTQ_20250829_1810_INCLUDE
