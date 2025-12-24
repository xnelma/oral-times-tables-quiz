#include "auto_locale.hpp"
#include "test_translation_resources.hpp"
#include <QLocale>
#include <gtest/gtest.h>
#include <exception>

TEST(AutoLocaleTest, FindsUniqueResource)
{
    TestTranslationResources::get().clear();

    // Prepare one entry that also is the match.
    auto match = Tts::LocaleDescriptor(QLocale::English, QLocale::UnitedStates);
    QLocale::setDefault(QLocale(match.language, match.territory));
    TestTranslationResources::get().insert({ match, "" });
    auto expected = match;

    Tts::LocaleDescriptor result = Tts::AutoLocale<TestTranslationResources>();
    EXPECT_EQ(result, expected);

    // Insert more entries, all different in locale and territory; keep 'match'
    // the same.
    TestTranslationResources::get().insert(
        { { Tts::LocaleDescriptor(QLocale::German, QLocale::Germany), "" },
          { Tts::LocaleDescriptor(QLocale::French, QLocale::France), "" } });

    result = Tts::AutoLocale<TestTranslationResources>();
    EXPECT_EQ(result, expected);

    // Insert another entry and change 'match'.
    TestTranslationResources::get().insert(
        { Tts::LocaleDescriptor(QLocale::Italian, QLocale::Italy), "" });
    match.language = QLocale::French;
    match.territory = QLocale::France;
    QLocale::setDefault(QLocale(match.language, match.territory));
    expected = match;

    result = Tts::AutoLocale<TestTranslationResources>();
    EXPECT_EQ(result, expected);
}

TEST(AutoLocaleTest, ThrowsForEmptyResources)
{
    TestTranslationResources::get().clear();
    EXPECT_THROW(Tts::AutoLocale<TestTranslationResources>(),
                 std::invalid_argument);
}

TEST(AutoLocaleTest, UsesSystemLocaleForSameLanguageMissingTerritory)
{
    TestTranslationResources::get().clear();

    QLocale::setDefault(QLocale(QLocale::English, QLocale::Germany));
    TestTranslationResources::get().insert(
        { Tts::LocaleDescriptor(QLocale::English, QLocale::UnitedStates), "" });

    auto expected = Tts::LocaleDescriptor(QLocale::English, QLocale::Germany);

    Tts::LocaleDescriptor result = Tts::AutoLocale<TestTranslationResources>();
    EXPECT_EQ(result, expected);
}
