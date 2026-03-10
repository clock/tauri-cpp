cmake_minimum_required(VERSION 3.30)

project(tauri_cpp VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(TAURI_CPP_BUILD_TESTS "Build tauri_cpp tests" ON)

add_library(tauri_cpp
  src/app_builder.cpp
  src/event_bus.cpp
)

target_include_directories(tauri_cpp
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(tauri_cpp PUBLIC cxx_std_20)

target_compile_options(tauri_cpp
  PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive- /EHsc>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

if(TAURI_CPP_BUILD_TESTS)
  include(FetchContent)

  FetchContent_Declare(
    doctest
    URL https://github.com/doctest/doctest/archive/refs/tags/v2.4.12.zip
  )
  FetchContent_MakeAvailable(doctest)

  enable_testing()

  add_executable(tauri_cpp_tests
    tests/app_builder_tests.cpp
  )

  target_link_libraries(tauri_cpp_tests
    PRIVATE
      tauri_cpp
      doctest::doctest
  )

  include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
  doctest_discover_tests(tauri_cpp_tests)
endif()
