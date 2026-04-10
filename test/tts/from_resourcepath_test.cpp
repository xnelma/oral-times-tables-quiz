#include "locale_descriptor.hpp"
#include <gtest/gtest.h>

TEST(FromResourcePathTest, DefaultForEmptyPath)
{
    Tts::LocaleDescriptor result, expected;
    result = Tts::LocaleDescriptor::fromResourcePath("");

    EXPECT_EQ(result, expected);
}

TEST(FromResourcePathTest, DefaultForMissingFilename)
{
    Tts::LocaleDescriptor result, expected;
    result = Tts::LocaleDescriptor::fromResourcePath("test/");

    EXPECT_EQ(result, expected);
}

TEST(FromResourcePathTest, ParsesValidPath)
{
    Tts::LocaleDescriptor result, expected;
    result = Tts::LocaleDescriptor::fromResourcePath(
        "test/en_DE." TRANSLATION_FILE_ENDING);

    expected = Tts::LocaleDescriptor(Tts::English, Tts::Germany);
    EXPECT_EQ(result, expected);
}
