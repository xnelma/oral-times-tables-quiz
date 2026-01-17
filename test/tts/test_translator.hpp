#ifndef OTTQ_20260109_1448_INCLUDE
#define OTTQ_20260109_1448_INCLUDE

#include "abstract_translator.hpp"
#include <QString>
#include <string>

namespace TtsTest {

enum Locale { En, De };

namespace ResourcePaths {

const QString en = "my/filepath/en";
const QString de = "my/filepath/de";

} // namespace ResourcePaths

class Translator : public Tts::AbstractTranslator
{
private:
    std::unordered_map<QString, Locale> translations_;
    QString filePath_;

public:
    Translator() { }

    void setup(const std::unordered_map<QString, Locale> &translations,
               const QString &filePath)
    {
        translations_ = std::move(translations);
        filePath_ = std::move(filePath);
    }

    static void permutate(std::string &str, const Locale &locale)
    {
        for (int i = 0; i <= static_cast<int>(locale); ++i)
            std::ranges::next_permutation(str.begin(), str.end());
    }

    QString filePath() override { return filePath_; }

    Tts::LocaleDescriptor localeDescriptor() override
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

    QLocale locale() override
    {
        auto ld = localeDescriptor();
        return QLocale(ld.language, ld.territory);
    }

    // NOLINTBEGIN(bugprone-easily-swappable-parameters)
    QString translate(const char *context, const char *sourceText,
                      const char *disambiguation = nullptr, int n = -1) override
    // NOLINTEND(bugprone-easily-swappable-parameters)
    {
        std::string sourceTextStr{ sourceText };
        permutate(sourceTextStr, translations_.at(filePath_));
        return QString::fromStdString(sourceTextStr);
    }

    bool load(const QString &filename) override
    {
        if (!translations_.contains(filename))
            throw std::invalid_argument(
                std::format("Resource path \"{}\" does not exist.",
                            filename.toStdString()));

        filePath_ = filename;
        return true;
    }
};

} // namespace TtsTest

#endif // OTTQ_20260109_1448_INCLUDE
