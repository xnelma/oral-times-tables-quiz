#include "locale_descriptor.hpp"
#include <gtest/gtest.h>
#include <exception>
#include <vector>
#include <string>

TEST(FromFileNameTest, ParsesNameWithLanguageOnly)
{
    Tts::LocaleDescriptor result, expected;
    result = Tts::LocaleDescriptor::fromFileName("en.qm");
    expected = Tts::LocaleDescriptor(QLocale::English, QLocale::AnyTerritory);
    EXPECT_EQ(result, expected);
}

TEST(FromFileNameTest, ParsesNameWithLanguageAndTerritory)
{
    Tts::LocaleDescriptor result, expected;
    result = Tts::LocaleDescriptor::fromFileName("en_US.qm");
    expected = Tts::LocaleDescriptor(QLocale::English, QLocale::UnitedStates);

    EXPECT_EQ(result, expected);

    result = Tts::LocaleDescriptor::fromFileName("en-US.qm");
    EXPECT_EQ(result, expected);
}

TEST(FromFileNameTest, ThrowsForMissingLanguage)
{
    EXPECT_THROW(Tts::LocaleDescriptor::fromFileName("US.qm"),
                 std::invalid_argument);
}

TEST(FromFileNameTest, ThrowsForInvalidName)
{
    std::vector<std::string> names = { "asdfghj", "US", "en_US", "en",
                                       "_",       "-",  "qm" };
    for (auto n : names)
        EXPECT_THROW(Tts::LocaleDescriptor::fromFileName(n),
                     std::invalid_argument);
}
