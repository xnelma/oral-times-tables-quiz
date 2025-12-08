add_library(Tts STATIC
    tts_settings.cpp
    tts_language_settings.cpp
    self_updating_translator.cpp
    tts_rate_settings.cpp
)

target_link_libraries(Tts PRIVATE
    Qt6::Quick
    Qt6::Core
)

target_include_directories(Tts PRIVATE
    "${PROJECT_SOURCE_DIR}/include/tts"
)
