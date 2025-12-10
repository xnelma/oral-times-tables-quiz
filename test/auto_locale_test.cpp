#include "auto_locale.hpp"
#include "test_translator.hpp"
#include <QLocale>
#include <gtest/gtest.h>

TEST(AutoLocaleTest, FindsMatchingResource)
{
    auto match = Tts::LocaleDescriptor(QLocale::English, QLocale::Germany);

    QLocale::setDefault(QLocale(match.language, match.territory));
    TestTranslator::resources().insert({ match, "" });

    Tts::LocaleDescriptor result = Tts::autoLocale<TestTranslator>();

    auto expected = match;

    EXPECT_EQ(result, expected);
}
