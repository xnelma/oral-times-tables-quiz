set(TtsSources)
list(APPEND TtsSources
    tts_settings.cpp
    locale_descriptor.cpp
    translation_resources.cpp
)

if(${Translator} MATCHES QT_TRANSLATOR)
list(APPEND TtsSources
    qt_translator.cpp
)
elseif(${Translator} MATCHES BOOST_TRANSLATOR)
list(APPEND TtsSources
    boost_translator.cpp
    boost_translation_dir.cpp
)
endif()

add_library(Tts STATIC ${TtsSources})

target_link_libraries(Tts PRIVATE
    Qt6::Quick
    Qt6::Core
)

if(${Translator} MATCHES BOOST_TRANSLATOR)
    target_link_libraries(Tts PRIVATE
        Boost::locale
    )
endif()

target_include_directories(Tts PRIVATE
    "${PROJECT_SOURCE_DIR}/include/tts"
)
