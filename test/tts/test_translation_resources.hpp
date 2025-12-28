#include "translation_resources.hpp"

struct TestTranslationResources : Tts::TranslationResources
{
    static Tts::ResourceMap &get()
    {
        static Tts::ResourceMap tmp;
        return tmp;
    }
};
