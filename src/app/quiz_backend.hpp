#ifndef OTTQ_20250829_1810_INCLUDE
#define OTTQ_20250829_1810_INCLUDE

#include "tts/quiz_translator.hpp"
#include "timestables/quiz.hpp"
#include <QObject>
#include <qqml.h>
#include <QLocale>
#include <QString>

class QuizBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double voiceRate READ voiceRate NOTIFY voiceRateChanged FINAL)
    Q_PROPERTY(QString question READ question NOTIFY questionChanged FINAL)
    // clang-format off
    Q_PROPERTY(QString localeName
               READ localeName
               NOTIFY localeNameChanged
               FINAL)
    Q_PROPERTY(bool isAvailable
               READ isAvailable
               WRITE setAvailability
               NOTIFY availabilityChanged
               FINAL)
    Q_PROPERTY(int numQuestionsRemaining
               READ numQuestionsRemaining
               NOTIFY numQuestionsRemainingChanged
               FINAL)
    // clang-format on
    QML_ELEMENT

public:
    explicit QuizBackend(QObject *parent = nullptr);

    QString localeName();
    double voiceRate();
    QString question();
    bool isAvailable();
    int numQuestionsRemaining();

    void setAvailability(const bool &isAvailable);

    Q_INVOKABLE bool setupQuiz(const QList<int> tables, const int minFactor,
                               const int maxFactor);
    Q_INVOKABLE void startQuiz();
    Q_INVOKABLE void check(const QString input);

signals:
    void localeNameChanged();
    void voiceRateChanged();
    void availabilityChanged();
    void numQuestionsRemainingChanged();
    void questionChanged();
    void quizCompleted();

private:
    void nextQuestion();

    Tts::QuizTranslator translator_;
    bool isAvailable_;
    TimesTables::Quiz quiz_;
    QString questionBase_;
};

#endif // OTTQ_20250829_1810_INCLUDE
