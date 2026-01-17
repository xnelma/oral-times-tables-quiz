#include "translation_resources.hpp"

namespace TtsTest {

struct TranslationResources : Tts::TranslationResources
{
    static Tts::ResourceMap &get()
    {
        static Tts::ResourceMap tmp;
        return tmp;
    }
};

} // namespace TtsTest
