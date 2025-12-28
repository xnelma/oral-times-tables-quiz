add_library(TimesTables STATIC
    quiz.cpp
)

target_link_libraries(TimesTables PRIVATE
    Qt6::Core
)

target_include_directories(TimesTables PRIVATE
    "${PROJECT_SOURCE_DIR}/include/timestables"
)
