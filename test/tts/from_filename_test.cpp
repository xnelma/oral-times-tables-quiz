#include "locale_descriptor.hpp"
#include <gtest/gtest.h>
#include <exception>
#include <vector>
#include <string>

TEST(FromFileNameTest, ParsesNameWithLanguageOnly)
{
    Tts::LocaleDescriptor result, expected;
    result = Tts::LocaleDescriptor::fromFileName("en." TRANSLATION_FILE_ENDING);
    expected = Tts::LocaleDescriptor(QLocale::English, QLocale::AnyTerritory);
    EXPECT_EQ(result, expected);
}

TEST(FromFileNameTest, ParsesNameWithLanguageAndTerritory)
{
    Tts::LocaleDescriptor result, expected;
    result =
        Tts::LocaleDescriptor::fromFileName("en_US." TRANSLATION_FILE_ENDING);
    expected = Tts::LocaleDescriptor(QLocale::English, QLocale::UnitedStates);

    EXPECT_EQ(result, expected);

    result =
        Tts::LocaleDescriptor::fromFileName("en-US." TRANSLATION_FILE_ENDING);
    EXPECT_EQ(result, expected);
}

TEST(FromFileNameTest, ThrowsForMissingLanguage)
{
    EXPECT_THROW(
        Tts::LocaleDescriptor::fromFileName("US." TRANSLATION_FILE_ENDING),
        std::invalid_argument);
}

TEST(FromFileNameTest, ThrowsForInvalidName)
{
    std::vector<std::string> names = {
        "asdfghj", "US", "en_US", "en", "_", "-", TRANSLATION_FILE_ENDING
    };
    for (auto n : names)
        EXPECT_THROW(Tts::LocaleDescriptor::fromFileName(n),
                     std::invalid_argument);
}
