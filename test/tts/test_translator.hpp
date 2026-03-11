#ifndef OTTQ_20260109_1448_INCLUDE
#define OTTQ_20260109_1448_INCLUDE

#ifdef BOOST_TRANSLATOR
#  undef BOOST_TRANSLATOR
#  define QT_TRANSLATOR // test only with std::string source text type
#endif

#include "abstract_translator.hpp"
#include <string>

namespace TtsTest {

enum Locale { En, De };

namespace ResourcePaths {

const std::string en = "my/filepath/en";
const std::string de = "my/filepath/de";

} // namespace ResourcePaths

class Translator : public Tts::AbstractTranslator
{
private:
    std::unordered_map<std::string, Locale> translations_;
    std::string filePath_;

public:
    Translator() { }

    void setup(const std::unordered_map<std::string, Locale> &translations,
               const std::string &filePath)
    {
        translations_ = std::move(translations);
        filePath_ = std::move(filePath);
    }

    static void permutate(std::string &str, const Locale &locale)
    {
        for (int i = 0; i <= static_cast<int>(locale); ++i)
            std::ranges::next_permutation(str.begin(), str.end());
    }

    std::string filePath() const override { return filePath_; }

    Tts::LocaleDescriptor localeDescriptor() const override
    {
        switch (translations_.at(filePath_)) {
        case Locale::En:
            return Tts::LocaleDescriptor(QLocale::English,
                                         QLocale::AnyTerritory);
        case Locale::De:
            return Tts::LocaleDescriptor(QLocale::German,
                                         QLocale::AnyTerritory);
        default: {
        }
        }

        return Tts::LocaleDescriptor(QLocale::C, QLocale::AnyTerritory);
    }

    std::string translate(const std::string &sourceText) const override
    {
        std::string tmp{ sourceText };
        permutate(tmp, translations_.at(filePath_));
        return tmp;
    }

    bool load(const std::string &filePath) override
    {
        if (!translations_.contains(filePath))
            throw std::invalid_argument("Resource path \"" + filePath
                                        + "\" does not exist.");

        filePath_ = filePath;
        return true;
    }
};

} // namespace TtsTest

#endif // OTTQ_20260109_1448_INCLUDE
