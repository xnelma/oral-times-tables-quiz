add_executable(AutoLocaleTest
    auto_locale_test.cpp
)

add_executable(LocaleDescriptorTest
    from_filename_test.cpp
)

add_executable(TranslatorUpdaterTest
    translator_updater_test.cpp
)

set(TestNames
    AutoLocaleTest
    LocaleDescriptorTest
    TranslatorUpdaterTest
)

foreach(TestName IN LISTS TestNames)
    target_link_libraries(${TestName} PRIVATE
        Qt6::Quick
        Tts
        GTest::gtest_main
    )

    target_include_directories(${TestName} PRIVATE
        "${PROJECT_SOURCE_DIR}/include/tts"
        "${PROJECT_SOURCE_DIR}/test/tts"
    )

    add_test(NAME ${TestName} COMMAND ${TestName})
endforeach()
