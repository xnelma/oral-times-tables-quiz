add_executable(AutoLocaleTest
    auto_locale_test.cpp
)

add_executable(LocaleDescriptorTest
    from_filename_test.cpp
    from_resourcepath_test.cpp
)

add_executable(SelfUpdatingTranslatorTest
    self_updating_translator_test.cpp
)

set(TestNames
    AutoLocaleTest
    LocaleDescriptorTest
    SelfUpdatingTranslatorTest
)

foreach(TestName IN LISTS TestNames)
    target_link_libraries(${TestName} PRIVATE
        Qt6::Quick
        Tts
        GTest::gtest_main
    )

    if(${Translator} MATCHES BOOST_TRANSLATOR)
        target_link_libraries(${TestName} PRIVATE
            Boost::locale
        )
    endif()

    target_include_directories(${TestName} PRIVATE
        "${PROJECT_SOURCE_DIR}/include/tts"
        "${PROJECT_SOURCE_DIR}/test/tts"
    )

    add_test(NAME ${TestName} COMMAND ${TestName})
endforeach()
