#ifndef OTTQ_20250829_1810_INCLUDE
#define OTTQ_20250829_1810_INCLUDE

#include "quiz_state_machine.hpp"
#include "quiz_config.hpp"
#include "tts/self_updating_translator.hpp"
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
    int numQuestionsRemaining();

    Q_INVOKABLE void startStateMachine(const QuizConfiguration &config);
    Q_INVOKABLE void check(const QString input);
    Q_INVOKABLE void sayQuestion();
    Q_INVOKABLE void stopStateMachine();

signals:
    void localeNameChanged();
    void numQuestionsRemainingChanged();
    void questionChanged();
    void stateChanged();
    void showLocaleError();

private:
    void setupStateMachine();
    double voiceRate();
    QString question();
    void nextQuestion();

    std::unique_ptr<QuizStateMachine> machine_;
    std::shared_ptr<QTextToSpeech> tts_;
    TimesTables::Quiz quiz_;
    QuizConfiguration quizConfig_;

    // The class outlives QuizView being on top of the stack, so the locale
    // can be updated in the settings and would need to be applied when
    // returning to the view. This would be handled inside the translator.
    Tts::SelfUpdatingTranslator translator_;
    QString questionBase_;
};

namespace QuizConstants {

static const char *const translationContext = "QuizView";
static const char *const questionBase = "%1 times %2";

} // namespace QuizConstants

#endif // OTTQ_20250829_1810_INCLUDE
