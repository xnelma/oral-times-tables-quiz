#include "translator.hpp"
#include "locale_descriptor.hpp"

Tts::Translator::Translator(QObject *parent) : translator_(parent) { }

QString Tts::Translator::filePath()
{
    return translator_.filePath();
}

QLocale Tts::Translator::locale()
{
    auto ld = Tts::LocaleDescriptor::fromResourcePath(filePath());
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
