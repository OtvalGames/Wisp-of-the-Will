cmake_minimum_required(VERSION 3.5)

project(yapg LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(yapg)

# Very bad practice
file(GLOB _HEADER_FILES_ CONFIGURE_DEPENDS "src/*.h" "src/*.hpp")
file(GLOB _SOURCE_FILES_ CONFIGURE_DEPENDS "src/*.c" "src/*.cpp")

target_sources(yapg PRIVATE ${_HEADER_FILES_} ${_SOURCE_FILES_})

add_custom_command(
  TARGET yapg
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res/
          $<TARGET_FILE_DIR:yapg>/res)

find_package(
  SFML
  COMPONENTS graphics window system
  REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(yapg sfml-graphics sfml-window sfml-system)

set_target_properties(yapg PROPERTIES LINK_FLAGS_RELEASE -s)

install(TARGETS yapg LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
