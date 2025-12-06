add_library(Tts STATIC
    tts_settings.cpp
    tts_language_settings.cpp
    quiz_translator.cpp
    tts_rate_settings.cpp
    translator_resources.cpp
)

target_link_libraries(Tts PRIVATE
    Qt6::Quick
    Qt6::Core
)

target_include_directories(Tts PRIVATE
    "${PROJECT_SOURCE_DIR}/include/tts"
)
