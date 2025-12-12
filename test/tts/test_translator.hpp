#include "self_updating_translator.hpp"
#include <QLocale>

struct TestTranslator : Tts::SelfUpdatingTranslator
{
    static Tts::ResourceMap &resources()
    {
        static Tts::ResourceMap tmp;
        return tmp;
    }
};
