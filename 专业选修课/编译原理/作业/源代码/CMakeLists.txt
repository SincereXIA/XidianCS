cmake_minimum_required(VERSION 3.12)
project(mysql VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)

# Boost Karma (part of Boost Spirir) has ability to handle output
option(USE_BOOST_KARMA "Use Boost Karma for output instead of doing it ourselves?" ON)
if(USE_BOOST_KARMA)
    find_package(Boost)
    if (Boost_FOUND)
        add_definitions("-DUSE_BOOST_KARMA")
    endif (Boost_FOUND)
endif(USE_BOOST_KARMA)
include_directories(${PROJECT_SOURCE_DIR}/include)
add_library(bprinter STATIC
        include/bprinter/table_printer.h
        include/bprinter/impl/table_printer.tpp.h
        table_printer.cpp
        include/database.h
        )
add_executable(mysql  database.cpp include/database.h sql.tab.cpp sql.tab.h myarray.cpp include/myarray.h dbCore.cpp include/dbCore.h test.cpp dbShell.cpp include/dbShell.h)
add_custom_command(OUTPUT sql.tab.cpp
    COMMAND bison -t ${PROJECT_SOURCE_DIR}/sql.y
    COMMAND flex  ${PROJECT_SOURCE_DIR}/sql.l
    COMMAND move ${CMAKE_BINARY_DIR}\\sql.tab.c ${CMAKE_BINARY_DIR}\\sql.tab.cpp)
target_link_libraries(mysql bprinter)
add_custom_command(TARGET mysql
        POST_BUILD
        COMMAND move ${CMAKE_BINARY_DIR}\\sql.tab.cpp ${CMAKE_BINARY_DIR}\\sql.tab.c)

set(BP_TARGET_NAME ${PROJECT_NAME})
set(BP_PACKAGE_NAME ${BP_TARGET_NAME})
set(BP_CONFIG_IN_FILENAME "config.cmake.in")
set(BP_CONFIG_FILENAME "${BP_PACKAGE_NAME}Config.cmake")
set(BP_CONFIGVERSION_FILENAME "${BP_PACKAGE_NAME}ConfigVersion.cmake")
set(BP_CONFIG_DESTINATION "cmake")
set(BP_INCLUDE_INSTALL_DIR "include/bprinter")
set(BP_LIB_INSTALL_DIR lib)

include(CMakePackageConfigHelpers)
configure_package_config_file(${BP_CONFIG_IN_FILENAME} ${CMAKE_CURRENT_BINARY_DIR}/${BP_CONFIG_FILENAME}
        INSTALL_DESTINATION ${BP_CONFIG_DESTINATION}
        PATH_VARS BP_INCLUDE_INSTALL_DIR BP_LIB_INSTALL_DIR)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/${BP_CONFIGVERSION_FILENAME}
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion)

INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/${BP_CONFIG_FILENAME} ${CMAKE_CURRENT_BINARY_DIR}/${BP_CONFIGVERSION_FILENAME}
        DESTINATION ${BP_CONFIG_DESTINATION})

INSTALL(TARGETS bprinter
        DESTINATION ${BP_LIB_INSTALL_DIR}
        PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)

INSTALL(FILES include/bprinter/table_printer.h
        DESTINATION ${BP_INCLUDE_INSTALL_DIR}
        PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)

INSTALL(FILES include/bprinter/impl/table_printer.tpp.h
        DESTINATION ${BP_INCLUDE_INSTALL_DIR}/impl
        PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
