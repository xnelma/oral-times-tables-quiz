qt_add_executable(OTTQ main.cpp)

target_link_libraries(OTTQ PRIVATE
    Qt6::Quick
    Qt6::TextToSpeech
    TimesTables
)

target_include_directories(OTTQ PRIVATE
    "${PROJECT_SOURCE_DIR}/include/TimesTables"
)

qt_add_qml_module(OTTQ
    URI OttqApp
    VERSION 0.1
    QML_FILES
        Main.qml
        SetupView.qml
        QuizView.qml
        SettingsView.qml
    SOURCES
        backend.hpp
        backend.cpp
)

qt_add_translations(OTTQ
     TS_FILE_BASE qml
     TS_FILE_DIR i18n
     RESOURCE_PREFIX qt/qml/OttqApp/i18n
)
