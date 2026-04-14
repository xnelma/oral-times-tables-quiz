#include "boost_translation_dir.hpp"

#include <stdexcept>
#include <filesystem>

std::string Tts::translationDir()
{
    static std::string translationPath;
    if (!translationPath.empty())
        return translationPath;

    if (std::filesystem::exists(TRANSLATION_DIR)) {
        translationPath = TRANSLATION_DIR;
        return translationPath;
    }

    auto cur = std::filesystem::current_path();
    // Only check a few parent directories as the nesting is not deep for this
    // project. E.g. the executable might be started from src/app with the
    // translation files in src/timestables, which would be just the second
    // parent.
    for (int i = 0; i < 3; ++i) {
        if (!cur.has_parent_path())
            break;
        cur = cur.parent_path();
        std::string candidate = cur.string() + "/" + TRANSLATION_DIR;
        if (std::filesystem::exists(candidate)) {
            translationPath = candidate;
            break;
        }
    }
    if (translationPath.empty())
        throw std::invalid_argument(
            "Invalid translation directory \'" + std::string(translationPath)
            + "\' (Current directory: \'"
            + std::filesystem::current_path().string() + "\')");

    return translationPath;
}