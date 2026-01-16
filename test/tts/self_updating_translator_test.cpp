#include "test_translator.hpp"
#include "self_updating_translator.hpp"
#include "test_tts_settings.hpp"
#include <QLocale>
#include <gtest/gtest.h>
#include <string>

TEST(TestTranslatorTest, TestTranslatorWorks)
{
    std::unordered_map<QString, TtsTest::Locale> translations;
    translations.insert({ TtsTest::ResourcePaths::en, TtsTest::Locale::En });
    translations.insert({ TtsTest::ResourcePaths::de, TtsTest::Locale::De });

    TtsTest::Translator translator;
    translator.setup(translations, TtsTest::ResourcePaths::en);

    EXPECT_EQ(translator.localeDescriptor(),
              Tts::LocaleDescriptor(QLocale::English, QLocale::AnyTerritory));
    EXPECT_EQ(translator.filePath(), TtsTest::ResourcePaths::en);
    std::string test = "test";
    QString res = translator.translate(nullptr, test.c_str());
    TtsTest::Translator::permutate(test, TtsTest::Locale::En);
    EXPECT_EQ(res, QString::fromStdString(test));

    translator.load(TtsTest::ResourcePaths::de);

    EXPECT_EQ(translator.localeDescriptor(),
              Tts::LocaleDescriptor(QLocale::German, QLocale::AnyTerritory));
    EXPECT_EQ(translator.filePath(), TtsTest::ResourcePaths::de);
    test = "test";
    res = translator.translate(nullptr, test.c_str());
    TtsTest::Translator::permutate(test, TtsTest::Locale::De);
    EXPECT_EQ(res, QString::fromStdString(test));
}

class SelfUpdatingTranslatorTest : public testing::Test
{
protected:
    SelfUpdatingTranslatorTest()
    {
        TestTranslationResources::get().insert(
            { enAny_, TtsTest::ResourcePaths::en });
        TestTranslationResources::get().insert(
            { deAny_, TtsTest::ResourcePaths::de });

        settings_ = std::make_shared<TestSettings>();
        settings_->saveLocaleSetting(enAny_);
        settings_->saveAutoLocaleSetting(false);
        translator_ = std::make_shared<
            Tts::SelfUpdatingTranslator<TtsTest::Translator,
                                        TestTranslationResources>>(settings_);

        QLocale::setDefault(QLocale(enUs_.language, enUs_.territory));

        std::unordered_map<QString, TtsTest::Locale> translations;
        translations.insert(
            { TtsTest::ResourcePaths::en, TtsTest::Locale::En });
        translations.insert(
            { TtsTest::ResourcePaths::de, TtsTest::Locale::De });
        translator_->setup(translations, TtsTest::ResourcePaths::en);
    }

    // NOLINTBEGIN(cppcoreguidelines-non-private-member-variables-in-classes)
    std::shared_ptr<TestSettings> settings_;
    std::shared_ptr<Tts::SelfUpdatingTranslator<TtsTest::Translator,
                                                TestTranslationResources>>
        translator_;

    Tts::LocaleDescriptor enUs_{ QLocale::English, QLocale::UnitedStates };
    Tts::LocaleDescriptor deDe_{ QLocale::German, QLocale::Germany };
    Tts::LocaleDescriptor enAny_{ QLocale::English, QLocale::AnyTerritory };
    Tts::LocaleDescriptor deAny_{ QLocale::German, QLocale::AnyTerritory };

    std::string test1_ = "test1";
    std::string test2_ = "test2";
    // NOLINTEND(cppcoreguidelines-non-private-member-variables-in-classes)
};

TEST_F(SelfUpdatingTranslatorTest, CatchesSettingsUpdate)
{
    Tts::LocaleDescriptor translatorLocale = translator_->localeDescriptor();
    EXPECT_EQ(translatorLocale, enAny_);

    QString result = translator_->translate(nullptr, test1_.c_str());
    TtsTest::Translator::permutate(test1_, TtsTest::Locale::En);
    EXPECT_EQ(result, QString::fromStdString(test1_));

    // update settings with new locale
    settings_->saveLocaleSetting(deAny_);

    result = translator_->translate(nullptr, test2_.c_str());
    TtsTest::Translator::permutate(test2_, TtsTest::Locale::De);
    EXPECT_EQ(result.toStdString(), test2_);

    translatorLocale = translator_->localeDescriptor();
    EXPECT_EQ(translatorLocale, deAny_);
}

TEST_F(SelfUpdatingTranslatorTest, CatchesSystemLocaleUpdate)
{
    settings_->saveAutoLocaleSetting(true);

    EXPECT_EQ(settings_->resolvedLocale(), enUs_);
    EXPECT_EQ(settings_->resolvedLocale().resourceKey(), enAny_);

    Tts::LocaleDescriptor translatorLocale = translator_->localeDescriptor();
    EXPECT_EQ(translatorLocale, enAny_);

    QString result = translator_->translate(nullptr, test1_.c_str());
    TtsTest::Translator::permutate(test1_, TtsTest::Locale::En);
    EXPECT_EQ(result, QString::fromStdString(test1_));

    // update system locale
    QLocale::setDefault(QLocale(deDe_.language, deDe_.territory));
    EXPECT_EQ(settings_->resolvedLocale(), deDe_);
    EXPECT_EQ(settings_->resolvedLocale().resourceKey(), deAny_);

    result = translator_->translate(nullptr, test2_.c_str());
    TtsTest::Translator::permutate(test2_, TtsTest::Locale::De);
    EXPECT_EQ(result, QString::fromStdString(test2_));

    translatorLocale = translator_->localeDescriptor();
    EXPECT_EQ(translatorLocale, deAny_);
}
