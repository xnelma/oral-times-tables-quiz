#include "tts_singleton.hpp"
#include "tts/auto_locale.hpp"
#include "tts/tts_settings.hpp"

TtsSingleton::TtsSingleton() : tts_(std::make_shared<QTextToSpeech>()) { }

TtsSingleton &TtsSingleton::instance()
{
    return initializedInstance();
}

void TtsSingleton::init()
{
    initializedInstance();
}

TtsSingleton &TtsSingleton::initializedInstance()
{
    static TtsSingleton tts;
    return tts;
}

void TtsSingleton::setup(const QLocale l, const double rate)
{
    tts_->setLocale(QLocale(l.language(), l.territory()));
    // FIXME QLocale::system() and QLocale(l_sys.language(), l_sys.territory())
    // compare to different objects, and trying to set the former as tts locale
    // causes tts to get into error state.
    // Before I created a new object in qml anyways, so I did not notice it.
    tts_->setRate(rate);
}

bool TtsSingleton::isReady()
{
    return tts_->state() == QTextToSpeech::Ready;
}

void TtsSingleton::say(const QString text)
{
    tts_->enqueue(text);
}

std::shared_ptr<const QTextToSpeech> TtsSingleton::get()
{
    return tts_;
}
