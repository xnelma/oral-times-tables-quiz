add_library(TimesTables STATIC
    placeholder.cpp
)

target_include_directories(TimesTables PRIVATE
    "${PROJECT_SOURCE_DIR}/include/TimesTables"
)
