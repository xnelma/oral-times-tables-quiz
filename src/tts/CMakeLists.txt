set(TtsSources)
list(APPEND TtsSources
    tts_settings.cpp
    locale_descriptor.cpp
    translation_resources.cpp
)

if(${Translator} MATCHES QT_TRANSLATOR)
list(APPEND TtsSources
    translator.cpp
)
endif()

add_library(Tts STATIC ${TtsSources})

target_link_libraries(Tts PRIVATE
    Qt6::Quick
    Qt6::Core
)

target_include_directories(Tts PRIVATE
    "${PROJECT_SOURCE_DIR}/include/tts"
)
