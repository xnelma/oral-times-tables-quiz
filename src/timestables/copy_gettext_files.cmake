file(GLOB_RECURSE moFiles "${CMAKE_CURRENT_LIST_DIR}/i18n/*/*.mo")
foreach (moFile ${moFiles})
    cmake_path(GET moFile STEM locale)

    set(destination "${CMAKE_CURRENT_BINARY_DIR}/i18n/${locale}/LC_MESSAGES")
    if (NOT EXISTS ${destination})
        file(MAKE_DIRECTORY ${destination})
    endif()

    file(COPY_FILE
        "${CMAKE_CURRENT_LIST_DIR}/i18n/${locale}/LC_MESSAGES/${locale}.mo"
        "${destination}/${locale}.mo"
        ONLY_IF_DIFFERENT)
endforeach()
