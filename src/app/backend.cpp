#include "backend.hpp"
#include "tts_singleton.hpp"

Backend::Backend(QObject *parent) : QObject(parent) { }

void Backend::initializeTts()
{
    TtsSingleton::init();
}
