#include "translator.hpp"
#include "locale_descriptor.hpp"

Tts::Translator::Translator(QObject *parent) : translator_(parent) { }

QString Tts::Translator::filePath()
{
    return translator_.filePath();
}

auto Tts::Translator::localeDescriptor() -> LocaleDescriptor
{
    return Tts::LocaleDescriptor::fromResourcePath(filePath());
}

QLocale Tts::Translator::locale()
{
    auto ld = localeDescriptor();
    return QLocale(ld.language, ld.territory);
}

QString Tts::Translator::translate(const char *context, const char *sourceText,
                                   const char *disambiguation, int n)
{
    return translator_.translate(context, sourceText, disambiguation, n);
}

bool Tts::Translator::load(const QString &filename)
{
    return translator_.load(filename);
}
