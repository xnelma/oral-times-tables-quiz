cmake_minimum_required(VERSION 3.19)
# Since 3.19 qt_finalize_target is called as part of qt_add_executable,
# according to the documentation.
# Don't allow for versions where the call needs to be done manually.

project(OralTimesTablesQuiz VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Needed by clang-tidy

find_package(Qt6
    REQUIRED COMPONENTS
        Quick
        Core
        LinguistTools
        TextToSpeech
        Test
        StateMachine
)
find_package(Boost
    REQUIRED COMPONENTS
        locale
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

# Set up translator:
# Use capital letters for the names because they are used as cpp text macros.
set(TranslatorImplementations QT_TRANSLATOR)
set(Translator QT_TRANSLATOR)
if(NOT ${Translator} IN_LIST TranslatorImplementations)
    message(FATAL_ERROR
            "-- Could NOT find translator implementation ${Translator} "
            "(Should be one of ${TranslatorImplementations})")
endif()
add_compile_definitions(${Translator})
if(${Translator} MATCHES QT_TRANSLATOR)
    set(TRANSLATION_DOMAIN "Translator")
endif()
add_compile_definitions(TRANSLATION_DOMAIN="${TRANSLATION_DOMAIN}")

qt_standard_project_setup(
    REQUIRES 6.7 # Qt 6.8 upwards only supports Android 9 upwards
    I18N_TRANSLATED_LANGUAGES de
)

add_subdirectory(src/app)
add_subdirectory(src/timestables)
add_subdirectory(src/tts)
if(NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Android")
    # don't cross compile the unit tests for now
    add_subdirectory(test)
endif()
