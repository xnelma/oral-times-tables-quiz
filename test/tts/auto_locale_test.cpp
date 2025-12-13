#include "auto_locale.hpp"
#include "test_translator.hpp"
#include <QLocale>
#include <gtest/gtest.h>
#include <exception>

TEST(AutoLocaleTest, FindsUniqueResource)
{
    TestTranslator::resources().clear();

    // Prepare one entry that also is the match.
    auto match = Tts::LocaleDescriptor(QLocale::English, QLocale::UnitedStates);
    QLocale::setDefault(QLocale(match.language, match.territory));
    TestTranslator::resources().insert({ match, "" });
    auto expected = match;

    Tts::LocaleDescriptor result = Tts::autoLocale<TestTranslator>();
    EXPECT_EQ(result, expected);

    // Insert more entries, all different in locale and territory; keep 'match'
    // the same.
    TestTranslator::resources().insert(
        { { Tts::LocaleDescriptor(QLocale::German, QLocale::Germany), "" },
          { Tts::LocaleDescriptor(QLocale::French, QLocale::France), "" } });

    result = Tts::autoLocale<TestTranslator>();
    EXPECT_EQ(result, expected);

    // Insert another entry and change 'match'.
    TestTranslator::resources().insert(
        { Tts::LocaleDescriptor(QLocale::Italian, QLocale::Italy), "" });
    match.language = QLocale::French;
    match.territory = QLocale::France;
    QLocale::setDefault(QLocale(match.language, match.territory));
    expected = match;

    result = Tts::autoLocale<TestTranslator>();
    EXPECT_EQ(result, expected);
}

TEST(AutoLocaleTest, ThrowsForEmptyResources)
{
    TestTranslator::resources().clear();
    EXPECT_THROW(Tts::autoLocale<TestTranslator>(), std::invalid_argument);
}

TEST(AutoLocaleTest, UsesSystemLocaleForSameLanguageMissingTerritory)
{
    TestTranslator::resources().clear();

    QLocale::setDefault(QLocale(QLocale::English, QLocale::Germany));
    TestTranslator::resources().insert(
        { Tts::LocaleDescriptor(QLocale::English, QLocale::UnitedStates), "" });

    auto expected = Tts::LocaleDescriptor(QLocale::English, QLocale::Germany);

    Tts::LocaleDescriptor result = Tts::autoLocale<TestTranslator>();
    EXPECT_EQ(result, expected);
}
