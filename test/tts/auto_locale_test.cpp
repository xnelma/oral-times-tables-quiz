#include "auto_locale_descriptor.hpp"
#include "test_translation_resources.hpp"
#include <gtest/gtest.h>

TEST(AutoLocaleTest, FindsUniqueResource)
{
    TtsTest::TranslationResources::get().clear();

    // Prepare one entry that also is the match.
    auto match = Tts::LocaleDescriptor(Tts::en, Tts::US);
    Tts::Locale::setDefault(match.language, match.territory);
    TtsTest::TranslationResources::get().insert({ match, "" });
    auto expected = match;

    auto result = Tts::AutoLocaleDescriptor<TtsTest::TranslationResources>();
    EXPECT_EQ(result, expected);

    // Insert more entries, all different in locale and territory; keep 'match'
    // the same.
    TtsTest::TranslationResources::get().insert(
        { { Tts::LocaleDescriptor(Tts::de, Tts::DE), "" },
          { Tts::LocaleDescriptor(Tts::fr, Tts::FR), "" } });

    result = Tts::AutoLocaleDescriptor<TtsTest::TranslationResources>();
    EXPECT_EQ(result, expected);

    // Insert another entry and change 'match'.
    TtsTest::TranslationResources::get().insert(
        { Tts::LocaleDescriptor(Tts::it, Tts::IT), "" });
    match.language = Tts::fr;
    match.territory = Tts::FR;
    Tts::Locale::setDefault(match.language, match.territory);
    expected = match;

    result = Tts::AutoLocaleDescriptor<TtsTest::TranslationResources>();
    EXPECT_EQ(result, expected);
}

TEST(AutoLocaleTest, ThrowsForEmptyResources)
{
    TtsTest::TranslationResources::get().clear();
    EXPECT_THROW(Tts::AutoLocaleDescriptor<TtsTest::TranslationResources>(),
                 std::invalid_argument);
}

TEST(AutoLocaleTest, UsesSystemLocaleForSameLanguageMissingTerritory)
{
    TtsTest::TranslationResources::get().clear();

    Tts::Locale::setDefault(Tts::en, Tts::DE);
    TtsTest::TranslationResources::get().insert(
        { Tts::LocaleDescriptor(Tts::en, Tts::US), "" });

    auto expected = Tts::LocaleDescriptor(Tts::en, Tts::DE);

    auto result = Tts::AutoLocaleDescriptor<TtsTest::TranslationResources>();
    EXPECT_EQ(result, expected);
}

TEST(AutoLocaleTest, CatchesLanguageUpdate)
{
    Tts::LocaleDescriptor oldMatch = Tts::LocaleDescriptor(Tts::en, Tts::DE);
    Tts::LocaleDescriptor newMatch = Tts::LocaleDescriptor(Tts::de, Tts::DE);

    TtsTest::TranslationResources::get().clear();
    TtsTest::TranslationResources::get().insert(
        { { oldMatch, "" }, { newMatch, "" } });

    Tts::Locale::setDefault(oldMatch.language, oldMatch.territory);
    auto result = Tts::AutoLocaleDescriptor<TtsTest::TranslationResources>();
    EXPECT_EQ(result, oldMatch);

    Tts::Locale::setDefault(newMatch.language, newMatch.territory);
    result.update();
    EXPECT_EQ(result, newMatch);
}

TEST(AutoLocaleTest, CatchesTerritoryUpdateForSameLanguage)
{
    auto oldMatch = Tts::LocaleDescriptor(Tts::en, Tts::DE);
    auto newMatch = Tts::LocaleDescriptor(Tts::en, Tts::UK);

    TtsTest::TranslationResources::get().clear();
    TtsTest::TranslationResources::get().insert(
        { { oldMatch, "" }, { newMatch, "" } });

    Tts::Locale::setDefault(oldMatch.language, oldMatch.territory);
    auto result = Tts::AutoLocaleDescriptor<TtsTest::TranslationResources>();
    EXPECT_EQ(result, oldMatch);

    Tts::Locale::setDefault(newMatch.language, newMatch.territory);
    result.update();
    EXPECT_EQ(result, newMatch);
}

TEST(AutoLocaleTest, CatchesTerritoryUpdateForDifferentLanguage)
{
    auto oldMatch = Tts::LocaleDescriptor(Tts::en, Tts::DE);
    auto newMatch = Tts::LocaleDescriptor(Tts::fr, Tts::FR);

    TtsTest::TranslationResources::get().clear();
    TtsTest::TranslationResources::get().insert(
        { { oldMatch, "" }, { newMatch, "" } });

    Tts::Locale::setDefault(oldMatch.language, oldMatch.territory);
    auto result = Tts::AutoLocaleDescriptor<TtsTest::TranslationResources>();
    EXPECT_EQ(result, oldMatch);

    Tts::Locale::setDefault(newMatch.language, newMatch.territory);
    result.update();
    EXPECT_EQ(result, newMatch);
}
