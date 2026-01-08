#include "translator.hpp"

Tts::Translator::Translator(QObject *parent) : translator_(parent) { }

QString Tts::Translator::filePath()
{
    return translator_.filePath();
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
