#ifndef OTTQ_20251014_2016_INCLUDE
#define OTTQ_20251014_2016_INCLUDE

#include "tts/locale_descriptor.hpp"
#include "tts/quiz_translator.hpp"
#include <QTextToSpeech>
#include <QString>
#include <memory>

class TtsSingleton
{
public:
    TtsSingleton(const TtsSingleton &) = delete;
    TtsSingleton(const TtsSingleton &&) = delete;
    TtsSingleton &operator=(const TtsSingleton &) = delete;
    TtsSingleton &operator=(const TtsSingleton &&) = delete;

    static TtsSingleton &instance();
    static void init();

    void setup(const QLocale l, const double rate);
    bool isReady();
    void say(const QString text);
    std::shared_ptr<const QTextToSpeech> get();

private:
    TtsSingleton();
    ~TtsSingleton() = default;

    static TtsSingleton &initializedInstance();

    std::shared_ptr<QTextToSpeech> tts_;
};

#endif // OTTQ_20251014_2016_INCLUDE
