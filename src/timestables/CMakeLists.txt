add_library(TimesTables STATIC
    quiz.cpp
)

target_link_libraries(TimesTables PRIVATE
    Qt6::Core
)

if(${Translator} MATCHES BOOST_TRANSLATOR)
    add_custom_target(CopyI18n
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_LIST_DIR}/i18n ${CMAKE_CURRENT_BINARY_DIR}/i18n
    )
    add_dependencies(TimesTables CopyI18n)

    target_link_libraries(TimesTables PRIVATE
        Boost::locale
    )
endif()

target_include_directories(TimesTables PRIVATE
    "${PROJECT_SOURCE_DIR}/include/timestables"
)
