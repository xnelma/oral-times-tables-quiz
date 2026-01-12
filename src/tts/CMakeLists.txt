add_library(Tts STATIC
    tts_settings.cpp
    translator.cpp
    locale_descriptor.cpp
    translation_resources.cpp
)

target_link_libraries(Tts PRIVATE
    Qt6::Quick
    Qt6::Core
)

target_include_directories(Tts PRIVATE
    "${PROJECT_SOURCE_DIR}/include/tts"
)
