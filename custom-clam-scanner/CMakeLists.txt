cmake_minimum_required(VERSION 3.10)
project(ClamAVScannerGUI VERSION 0.1 LANGUAGES CXX)

# Enable debug output for CMake
set(CMAKE_VERBOSE_MAKEFILE ON)

# Qt configurations
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# C++ standard settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add compile warnings
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra)
endif()

# Find required packages
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core)
find_package(SQLite3 REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(CLAMAV REQUIRED libclamav)

# Backend source files
set(BACKEND_SOURCES
    src/Database.cpp
    src/scheduler.cpp
    src/quickscan.cpp
    src/systemscan.cpp
    src/customscan.cpp
    src/signatureupdater.cpp
    src/ScanWorker.cpp
)

# Backend headers
set(BACKEND_HEADERS
    include/Database.h
    include/scheduler.h
    include/quickscan.h
    include/systemscan.h
    include/customscan.h
    include/signatureupdater.h
    include/ScanWorker.h
)

# UI source files
set(UI_SOURCES
    ui/main.cpp
    ui/mainwindow.cpp
    ui/mainwindow.h
    ui/mainwindow.ui
    ui/scantypepage.cpp
    ui/scantypepage.h
    ui/scantypepage.ui
    ui/schedulescanpage.h
    ui/schedulescanpage.cpp
    ui/schedulescanpage.ui
    ui/historypage.h
    ui/historypage.cpp
    ui/historypage.ui
    ui/quarantinepage.h
    ui/quarantinepage.cpp
    ui/quarantinepage.ui
    ui/lastscanpage.h
    ui/lastscanpage.cpp
    ui/lastscanpage.ui
    ui/settingspage.h
    ui/settingspage.cpp
    ui/settingspage.ui
    ui/resources.qrc
)

# Database related files
set(DB_FILES
    scan_results.db
    scheduler.db
)

# Create the executable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ClamAVScannerGUI
        MANUAL_FINALIZATION
        ${BACKEND_SOURCES}
        ${BACKEND_HEADERS}
        ${UI_SOURCES}
    )
else()
    if(ANDROID)
        add_library(ClamAVScannerGUI SHARED
            ${BACKEND_SOURCES}
            ${BACKEND_HEADERS}
            ${UI_SOURCES}
        )
    else()
        add_executable(ClamAVScannerGUI
            ${BACKEND_SOURCES}
            ${BACKEND_HEADERS}
            ${UI_SOURCES}
        )
    endif()
endif()

# Include directories
target_include_directories(ClamAVScannerGUI PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/ui
    ${CMAKE_CURRENT_BINARY_DIR}
    ${SQLite3_INCLUDE_DIRS}
    ${CLAMAV_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(ClamAVScannerGUI PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    ${SQLite3_LIBRARIES}
    ${CLAMAV_LIBRARIES}
    stdc++fs
    pthread
)

# Create Quarantine directory
add_custom_command(TARGET ClamAVScannerGUI POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
    ${CMAKE_BINARY_DIR}/Quarantine
)

# Copy database files to build directory
foreach(DB_FILE ${DB_FILES})
    add_custom_command(TARGET ClamAVScannerGUI POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/${DB_FILE}
        ${CMAKE_BINARY_DIR}/${DB_FILE}
    )
endforeach()

# Set properties for different platforms
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ClamAVScannerGUI)
endif()

set_target_properties(ClamAVScannerGUI PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Installation
include(GNUInstallDirs)
install(TARGETS ClamAVScannerGUI
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Install database files
install(FILES ${DB_FILES}
    DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ClamAVScannerGUI)
endif()