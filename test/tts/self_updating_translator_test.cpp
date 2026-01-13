#include "test_translator.hpp"
#include "self_updating_translator.hpp"
#include "test_tts_settings.hpp"
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

TEST(TranslatorUpdaterTest, CatchesSettingsUpdate)
{
    TestTranslationResources::get().clear();
    auto sys = Tts::LocaleDescriptor(QLocale::English, QLocale::UnitedStates);
    auto cur = Tts::LocaleDescriptor(QLocale::English, QLocale::AnyTerritory);
    QLocale::setDefault(QLocale(sys.language, sys.territory));
    TestTranslationResources::get().insert({ cur, TtsTest::ResourcePaths::en });

    std::shared_ptr<TestSettings> settings = std::make_shared<TestSettings>();
    settings->saveLocaleSetting(cur);
    settings->saveAutoLocaleSetting(false);

    Tts::SelfUpdatingTranslator<TtsTest::Translator, TestTranslationResources>
        translator(settings);
    std::unordered_map<QString, TtsTest::Locale> translations;
    translations.insert({ TtsTest::ResourcePaths::en, TtsTest::Locale::En });
    translations.insert({ TtsTest::ResourcePaths::de, TtsTest::Locale::De });
    translator.setup(translations, TtsTest::ResourcePaths::en);

    Tts::LocaleDescriptor translatorLocale = translator.localeDescriptor();
    EXPECT_EQ(translatorLocale, cur);

    const char *test = "test";
    QString res = translator.translate(nullptr, test);
    std::string testStr{ test };
    TtsTest::Translator::permutate(testStr, TtsTest::Locale::En);
    EXPECT_EQ(res, QString::fromStdString(testStr));

    auto newCur = Tts::LocaleDescriptor(QLocale::German, QLocale::AnyTerritory);
    TestTranslationResources::get().insert(
        { newCur, TtsTest::ResourcePaths::de });

    // update settings with new locale
    settings->saveLocaleSetting(newCur);

    res = translator.translate(nullptr, test);
    testStr = test;
    TtsTest::Translator::permutate(testStr, TtsTest::Locale::De);
    EXPECT_EQ(res, QString::fromStdString(testStr));

    translatorLocale = translator.localeDescriptor();
    EXPECT_EQ(translatorLocale, newCur);
}

TEST(TranslatorUpdaterTest, CatchesSystemLocaleUpdate)
{
    TestTranslationResources::get().clear();
    auto sys = Tts::LocaleDescriptor(QLocale::English, QLocale::UnitedStates);
    auto curEn = Tts::LocaleDescriptor(QLocale::English, QLocale::AnyTerritory);
    auto curDe = Tts::LocaleDescriptor(QLocale::German, QLocale::AnyTerritory);
    QLocale::setDefault(QLocale(sys.language, sys.territory));
    TestTranslationResources::get().insert(
        { curEn, TtsTest::ResourcePaths::en });
    TestTranslationResources::get().insert(
        { curDe, TtsTest::ResourcePaths::de });

    std::shared_ptr<TestSettings> settings = std::make_shared<TestSettings>();
    settings->saveAutoLocaleSetting(true);
    EXPECT_EQ(settings->resolvedLocale(), sys);
    EXPECT_EQ(settings->resolvedLocale().resourceKey(), curEn);

    Tts::SelfUpdatingTranslator<TtsTest::Translator, TestTranslationResources>
        translator(settings);
    std::unordered_map<QString, TtsTest::Locale> translations;
    translations.insert({ TtsTest::ResourcePaths::en, TtsTest::Locale::En });
    translations.insert({ TtsTest::ResourcePaths::de, TtsTest::Locale::De });
    translator.setup(translations, TtsTest::ResourcePaths::en);

    Tts::LocaleDescriptor translatorLocale = translator.localeDescriptor();
    EXPECT_EQ(translatorLocale, curEn);

    const char *test = "test";
    QString res = translator.translate(nullptr, test);
    std::string testStr{ test };
    TtsTest::Translator::permutate(testStr, TtsTest::Locale::En);
    EXPECT_EQ(res, QString::fromStdString(testStr));

    // update system locale
    auto newSys = Tts::LocaleDescriptor(QLocale::German, QLocale::Germany);
    QLocale::setDefault(QLocale(newSys.language, newSys.territory));
    EXPECT_EQ(settings->resolvedLocale(), newSys);
    EXPECT_EQ(settings->resolvedLocale().resourceKey(), curDe);

    res = translator.translate(nullptr, test);
    testStr = test;
    TtsTest::Translator::permutate(testStr, TtsTest::Locale::De);
    EXPECT_EQ(res, QString::fromStdString(testStr));

    translatorLocale = translator.localeDescriptor();
    EXPECT_EQ(translatorLocale, curDe);
}
