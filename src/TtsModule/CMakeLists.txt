add_library(TtsModule STATIC
    tts_settings.cpp
    tts_language_settings.cpp
    quiz_translator.cpp
    auto_locale.cpp
)

target_link_libraries(TtsModule PRIVATE
    Qt6::Quick
    Qt6::Core
)

target_include_directories(TtsModule PRIVATE
    "${PROJECT_SOURCE_DIR}/include/TtsModule"
)
