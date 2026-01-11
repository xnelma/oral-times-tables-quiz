#include "translator_updater.hpp"
#include "test_translator.hpp"
#include <QLocale>
#include <gtest/gtest.h>
#include <string>

TEST(TranslatorUpdaterTest, TestTranslatorWorks)
{
    std::unordered_map<QString, TtsTest::Locale> translations;
    translations.insert({ TtsTest::ResourcePaths::en, TtsTest::Locale::En });
    translations.insert({ TtsTest::ResourcePaths::de, TtsTest::Locale::De });

    TtsTest::Translator translator;
    translator.setup(translations, TtsTest::ResourcePaths::en);

    EXPECT_EQ(translator.localeDescriptor(),
              Tts::LocaleDescriptor(QLocale::English, QLocale::AnyTerritory));
    EXPECT_EQ(translator.filePath(), TtsTest::ResourcePaths::en);
    const char *test = "test";
    QString res = translator.translate(nullptr, test);
    std::string testStr{ test };
    TtsTest::Translator::permutate(testStr, TtsTest::Locale::En);
    EXPECT_EQ(res, QString::fromStdString(testStr));

    translator.load(TtsTest::ResourcePaths::de);

    EXPECT_EQ(translator.localeDescriptor(),
              Tts::LocaleDescriptor(QLocale::German, QLocale::AnyTerritory));
    EXPECT_EQ(translator.filePath(), TtsTest::ResourcePaths::de);
    res = translator.translate(nullptr, test);
    testStr = test;
    TtsTest::Translator::permutate(testStr, TtsTest::Locale::De);
    EXPECT_EQ(res, QString::fromStdString(testStr));
}
