#ifndef OTTQ_20251014_2023_INCLUDE
#define OTTQ_20251014_2023_INCLUDE

#include <QSignalTransition>
#include <QStateMachine>
#include <QTextToSpeech>
#include <QObject>
#include <qqml.h>
#include <memory>

class TtsStateTransition : public QSignalTransition
{

public:
    TtsStateTransition(const std::shared_ptr<const QTextToSpeech> tts,
                       const QTextToSpeech::State &state)
        : QSignalTransition(tts.get(), &QTextToSpeech::stateChanged),
          tts_(tts),
          state_(state)
    {
    }

protected:
    bool eventTest(QEvent *e) override
    {
        if (!QSignalTransition::eventTest(e))
            return false;

        QStateMachine::SignalEvent *se =
            dynamic_cast<QStateMachine::SignalEvent *>(e);
        return tts_->state() == state_;
    }

    void onTransition(QEvent *) override { }

private:
    const std::shared_ptr<const QTextToSpeech> tts_;
    const QTextToSpeech::State state_;
};

#endif // OTTQ_20251014_2023_INCLUDE
