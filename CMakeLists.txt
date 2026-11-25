cmake_minimum_required(VERSION 3.15)
project(Scarlet-Dynamic-Layers-Testing LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Debug Release RelWithDebInfo MinSizeRel)
endif()

# ---------------------------------------------------------------------------
# Scarlet-Dynamic-Layers — header-only library (submodule, no build of its own)
# ---------------------------------------------------------------------------
add_library(scarlet_dynamic_layers INTERFACE)
add_library(Scarlet::DynamicLayers ALIAS scarlet_dynamic_layers)

# Core (sb / lb) headers
target_include_directories(scarlet_dynamic_layers INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/Scarlet-Dynamic-Layers/Source/Core/Include"
)

# User-facing headers (Stacks, Operations)
target_include_directories(scarlet_dynamic_layers INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/Scarlet-Dynamic-Layers/Source/User"
)

# ---------------------------------------------------------------------------
# doctest — vendored testing framework
# ---------------------------------------------------------------------------
# We provide our own main() via DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN in the test
# files, so doctest's own main/static-lib and example targets are not needed.
set(DOCTEST_WITH_MAIN_IN_STATIC_LIB OFF CACHE BOOL "" FORCE)
set(DOCTEST_WITH_TESTS               OFF CACHE BOOL "" FORCE)
set(DOCTEST_NO_INSTALL               ON  CACHE BOOL "" FORCE)

add_subdirectory(doctest EXCLUDE_FROM_ALL)

# ---------------------------------------------------------------------------
# Tests
# ---------------------------------------------------------------------------
# Every .cpp file in Tests/ is compiled into the test executable.
# Each file may define its own main() (DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN) —
# put that in exactly ONE file (see Tests/Test_StackBasicOperations.cpp).
file(GLOB DL_TEST_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Tests/*.cpp")
list(SORT DL_TEST_SOURCES)

if(NOT DL_TEST_SOURCES)
    message(FATAL_ERROR "No test sources found in ${CMAKE_CURRENT_SOURCE_DIR}/Tests")
endif()

add_executable(dl_tests ${DL_TEST_SOURCES})

target_link_libraries(dl_tests PRIVATE
    Scarlet::DynamicLayers
    doctest
)

# Register the test binary with CTest: `ctest` runs it once per executable.
enable_testing()
add_test(NAME dl_tests COMMAND dl_tests)
