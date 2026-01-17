#include "auto_locale.hpp"
#include "test_translation_resources.hpp"
#include <QLocale>
#include <gtest/gtest.h>
#include <exception>

TEST(AutoLocaleTest, FindsUniqueResource)
{
    TtsTest::TranslationResources::get().clear();

    // Prepare one entry that also is the match.
    auto match = Tts::LocaleDescriptor(QLocale::English, QLocale::UnitedStates);
    QLocale::setDefault(QLocale(match.language, match.territory));
    TtsTest::TranslationResources::get().insert({ match, "" });
    auto expected = match;

    auto result = Tts::AutoLocale<TtsTest::TranslationResources>();
    EXPECT_EQ(result, expected);

    // Insert more entries, all different in locale and territory; keep 'match'
    // the same.
    TtsTest::TranslationResources::get().insert(
        { { Tts::LocaleDescriptor(QLocale::German, QLocale::Germany), "" },
          { Tts::LocaleDescriptor(QLocale::French, QLocale::France), "" } });

    result = Tts::AutoLocale<TtsTest::TranslationResources>();
    EXPECT_EQ(result, expected);

    // Insert another entry and change 'match'.
    TtsTest::TranslationResources::get().insert(
        { Tts::LocaleDescriptor(QLocale::Italian, QLocale::Italy), "" });
    match.language = QLocale::French;
    match.territory = QLocale::France;
    QLocale::setDefault(QLocale(match.language, match.territory));
    expected = match;

    result = Tts::AutoLocale<TtsTest::TranslationResources>();
    EXPECT_EQ(result, expected);
}

TEST(AutoLocaleTest, ThrowsForEmptyResources)
{
    TtsTest::TranslationResources::get().clear();
    EXPECT_THROW(Tts::AutoLocale<TtsTest::TranslationResources>(),
                 std::invalid_argument);
}

TEST(AutoLocaleTest, UsesSystemLocaleForSameLanguageMissingTerritory)
{
    TtsTest::TranslationResources::get().clear();

    QLocale::setDefault(QLocale(QLocale::English, QLocale::Germany));
    TtsTest::TranslationResources::get().insert(
        { Tts::LocaleDescriptor(QLocale::English, QLocale::UnitedStates), "" });

    auto expected = Tts::LocaleDescriptor(QLocale::English, QLocale::Germany);

    auto result = Tts::AutoLocale<TtsTest::TranslationResources>();
    EXPECT_EQ(result, expected);
}

TEST(AutoLocaleTest, CatchesLanguageUpdate)
{
    Tts::LocaleDescriptor oldMatch =
        Tts::LocaleDescriptor(QLocale::English, QLocale::Germany);
    Tts::LocaleDescriptor newMatch =
        Tts::LocaleDescriptor(QLocale::German, QLocale::Germany);

    TtsTest::TranslationResources::get().clear();
    TtsTest::TranslationResources::get().insert(
        { { oldMatch, "" }, { newMatch, "" } });

    QLocale::setDefault(QLocale(oldMatch.language, oldMatch.territory));
    auto result = Tts::AutoLocale<TtsTest::TranslationResources>();
    EXPECT_EQ(result, oldMatch);

    QLocale::setDefault(QLocale(newMatch.language, newMatch.territory));
    result.update();
    EXPECT_EQ(result, newMatch);
}

TEST(AutoLocaleTest, CatchesTerritoryUpdateForSameLanguage)
{
    auto oldMatch = Tts::LocaleDescriptor(QLocale::English, QLocale::Germany);
    auto newMatch =
        Tts::LocaleDescriptor(QLocale::English, QLocale::UnitedKingdom);

    TtsTest::TranslationResources::get().clear();
    TtsTest::TranslationResources::get().insert(
        { { oldMatch, "" }, { newMatch, "" } });

    QLocale::setDefault(QLocale(oldMatch.language, oldMatch.territory));
    auto result = Tts::AutoLocale<TtsTest::TranslationResources>();
    EXPECT_EQ(result, oldMatch);

    QLocale::setDefault(QLocale(newMatch.language, newMatch.territory));
    result.update();
    EXPECT_EQ(result, newMatch);
}

TEST(AutoLocaleTest, CatchesTerritoryUpdateForDifferentLanguage)
{
    auto oldMatch = Tts::LocaleDescriptor(QLocale::English, QLocale::Germany);
    auto newMatch = Tts::LocaleDescriptor(QLocale::French, QLocale::France);

    TtsTest::TranslationResources::get().clear();
    TtsTest::TranslationResources::get().insert(
        { { oldMatch, "" }, { newMatch, "" } });

    QLocale::setDefault(QLocale(oldMatch.language, oldMatch.territory));
    auto result = Tts::AutoLocale<TtsTest::TranslationResources>();
    EXPECT_EQ(result, oldMatch);

    QLocale::setDefault(QLocale(newMatch.language, newMatch.territory));
    result.update();
    EXPECT_EQ(result, newMatch);
}
