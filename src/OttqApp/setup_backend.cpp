#include "setup_backend.hpp"

SetupBackend::SetupBackend(QObject *parent) : QObject{ parent } { }

QString SetupBackend::timesTableNumbers()
{
    return "";
}

int SetupBackend::minFactor()
{
    return 2;
}

int SetupBackend::maxFactor()
{
    return 20;
}

void SetupBackend::setMinFactor(const int min)
{
    int m = min;
}

void SetupBackend::setMaxFactor(const int max)
{
    int m = max;
}

void SetupBackend::addTimesTable(const int number)
{
    int n = number;
}
