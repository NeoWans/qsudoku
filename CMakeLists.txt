cmake_minimum_required(VERSION 3.5)

project(qsudoku VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-Wall -Wno-unused")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories("src")
include_directories("extern")

file(GLOB PROJECT_SOURCE "src/*")
file(GLOB EXTERNAL_SOURCE "extern/*")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
  qt_add_executable(qsudoku
    MANUAL_FINALIZATION
    ${PROJECT_SOURCE}
    ${EXTERNAL_SOURCE}
  )
# Define target properties for Android with Qt 6 as:
#  set_property(TARGET qsudoku APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#    ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
  if(ANDROID)
    add_library(qsudoku SHARED
      ${PROJECT_SOURCE}
      ${EXTERNAL_SOURCE}
    )
# Define properties for Android with Qt 5 after find_package() calls as:
#  set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
  else()
    add_executable(qsudoku
      ${PROJECT_SOURCE}
      ${EXTERNAL_SOURCE}
    )
  endif()
endif()

target_link_libraries(qsudoku PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(qsudoku PROPERTIES
  MACOSX_BUNDLE_GUI_IDENTIFIER q.sudoku.app
  MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
  MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
  MACOSX_BUNDLE TRUE
  WIN32_EXECUTABLE TRUE
)

install(TARGETS qsudoku
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
  qt_finalize_executable(qsudoku)
endif()
