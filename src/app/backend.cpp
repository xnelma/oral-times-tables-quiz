#include "backend.hpp"
#include "tts_singleton.hpp"

Backend::Backend(QObject *parent) : QObject(parent)
{
    TtsSingleton::init();
    // TODO can I create the tts instance in a different thread?
}
