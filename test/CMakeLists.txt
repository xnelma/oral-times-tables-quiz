include(FetchContent)
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    # while hashes are recommended due to being immutable, the googletest repo
    # can be taken as reliable as to not change the commit behind the tag (or
    # if they decide to do so, for a very good reason).
    # So maybe actually use a tag? because it is better to read?
    GIT_TAG v1.17.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE
    gtest_main
)

enable_testing()

add_executable(AutoLocaleTest
    auto_locale_test.cpp
)

target_link_libraries(AutoLocaleTest PRIVATE
    Qt6::Quick
    TimesTables
    GTest::gtest_main
)

target_include_directories(AutoLocaleTest PRIVATE
    "${PROJECT_SOURCE_DIR}/include/tts"
    "${PROJECT_SOURCE_DIR}/test"
)

include(GoogleTest)
add_test(NAME AutoLocaleTest COMMAND AutoLocaleTest)
