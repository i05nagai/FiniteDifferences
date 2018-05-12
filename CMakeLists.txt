cmake_minimum_required(VERSION 2.8.6)

project(fd CXX)

# Make sure we can import out CMake functions
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
# Import our CMake modules
include(AddCXXCompilerFlag)

#compiler option with accordance to compiler
IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    SET (CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
    SET (CMAKE_CXX_FLAGS "-Wno-unused-parameter ${CMAKE_CXX_FLAGS}")
    SET (CMAKE_CXX_FLAGS "-Wno-unused-private-field ${CMAKE_CXX_FLAGS}")
    SET (CMAKE_CXX_FLAGS "-Wno-missing-field-initializers ${CMAKE_CXX_FLAGS}")
    SET (CMAKE_CXX_FLAGS "-Wall -Wextra -Werror ${CMAKE_CXX_FLAGS}")
    # for debug
    SET (CMAKE_CXX_FLAGS_DEBUG, "-g ${CMAKE_CXX_FLAGS_DEBUG}")
    # for release
    SET (CMAKE_CXX_FLAGS_RELEASE "-O2 ${CMAKE_CXX_FLAGS_RELEASE}")
    # If profiling with gprof is on
    IF(FD_BUILD_WITH_PROFILE)
        SET (CMAKE_CXX_FLAGS "-pg ${CMAKE_CXX_FLAGS}")
        SET (CMAKE_CXX_FLAGS "-g ${CMAKE_CXX_FLAGS}")
    ENDIF()
ELSEIF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    SET (CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
    SET (CMAKE_CXX_FLAGS "-Wno-unused-parameter ${CMAKE_CXX_FLAGS}")
    SET (CMAKE_CXX_FLAGS "-Wno-unused-private-field ${CMAKE_CXX_FLAGS}")
    SET (CMAKE_CXX_FLAGS "-Wno-missing-field-initializers ${CMAKE_CXX_FLAGS}")
    SET (CMAKE_CXX_FLAGS "-Wall -Wextra -Werror ${CMAKE_CXX_FLAGS}")
    # for debug
    SET (CMAKE_CXX_FLAGS_DEBUG, "-g ${CMAKE_CXX_FLAGS_DEBUG}")
    ## for google perftools on Mac
    SET (CMAKE_CXX_FLAGS_DEBUG, "-Wl,-no_pie  ${CMAKE_CXX_FLAGS_DEBUG}")
    # for release
    SET (CMAKE_CXX_FLAGS_RELEASE "-O2 ${CMAKE_CXX_FLAGS_RELEASE}")
ELSEIF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    IF (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19)
        MESSAGE ( FATAL_ERROR "MSVC doesn't support C++11.")
    ENDIF ()
ENDIF ()

# include directory
INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/submodule/boost/array/include
    ${CMAKE_CURRENT_SOURCE_DIR}/submodule/boost/assert/include
    ${CMAKE_CURRENT_SOURCE_DIR}/submodule/boost/concept_check/include
    ${CMAKE_CURRENT_SOURCE_DIR}/submodule/boost/config/include
    ${CMAKE_CURRENT_SOURCE_DIR}/submodule/boost/core/include
    ${CMAKE_CURRENT_SOURCE_DIR}/submodule/boost/integer/include
    ${CMAKE_CURRENT_SOURCE_DIR}/submodule/boost/iterator/include
    ${CMAKE_CURRENT_SOURCE_DIR}/submodule/boost/math/include
    ${CMAKE_CURRENT_SOURCE_DIR}/submodule/boost/mpl/include
    ${CMAKE_CURRENT_SOURCE_DIR}/submodule/boost/numeric/ublas/include
    ${CMAKE_CURRENT_SOURCE_DIR}/submodule/boost/predef/include
    ${CMAKE_CURRENT_SOURCE_DIR}/submodule/boost/preprocessor/include
    ${CMAKE_CURRENT_SOURCE_DIR}/submodule/boost/random/include
    ${CMAKE_CURRENT_SOURCE_DIR}/submodule/boost/range/include
    ${CMAKE_CURRENT_SOURCE_DIR}/submodule/boost/serialization/include
    ${CMAKE_CURRENT_SOURCE_DIR}/submodule/boost/static_assert/include
    ${CMAKE_CURRENT_SOURCE_DIR}/submodule/boost/throw_exception/include
    ${CMAKE_CURRENT_SOURCE_DIR}/submodule/boost/type_traits/include
    ${CMAKE_CURRENT_SOURCE_DIR}/submodule/boost/typeof/include
    ${CMAKE_CURRENT_SOURCE_DIR}/submodule/boost/utility/include
    ${CMAKE_CURRENT_SOURCE_DIR}/submodule/googletest/googlemock/include
    ${CMAKE_CURRENT_SOURCE_DIR}/submodule/googletest/googletest/include
)

#inclue sources
INCLUDE(cmake/fd.cmake)

#add library
ADD_LIBRARY(fd ${fd_SOURCES})

# test
IF(FD_BUILD_TEST OR FD_BUILD_TEST_MEMORYCHECK)
#GTEST and GMOCK build
    SET(BUILD_GTEST ON CACHE BOOL "Use some expat option")
    ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/submodule/googletest)

    INCLUDE(cmake/fd_test.cmake)
    ENABLE_TESTING()

    ADD_EXECUTABLE(fd_test ${fd_test_SOURCES})
    TARGET_LINK_LIBRARIES(fd_test fd)
    TARGET_LINK_LIBRARIES(fd_test gmock)
    TARGET_LINK_LIBRARIES(fd_test gtest)
    ADD_TEST(fd_test fd_test)

    # memcheck
    IF(FD_BUILD_TEST_MEMORYCHECK)
        SET(MEMORYCHECK_COMMAND_OPTIONS "--leak-check=full --show-leak-kinds=definite,possible --error-exitcode=1")
        SET(MEMORYCHECK_SUPPRESSIONS_FILE "${PROJECT_SOURCE_DIR}/ci/valgrind_suppression.supp" )
        FIND_PROGRAM(CTEST_MEMORYCHECK_COMMAND NAMES valgrind)
        # Dart must be at the end of configuration
        INCLUDE(Dart)
    ENDIF()
ENDIF()

# if you enable an option by `-DCMAKE_BUILD_TYPE=Coverage`,
# add the coverage command(s)
if (${CMAKE_BUILD_TYPE} MATCHES "Coverage")
  # Coverage build type
  set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_DEBUG}" CACHE STRING
    "Flags used by the C++ compiler during coverage builds."
    FORCE)
  set(CMAKE_EXE_LINKER_FLAGS_COVERAGE
    "${CMAKE_EXE_LINKER_FLAGS_DEBUG}" CACHE STRING
    "Flags used for linking binaries during coverage builds."
    FORCE)
  set(CMAKE_SHARED_LINKER_FLAGS_COVERAGE
    "${CMAKE_SHARED_LINKER_FLAGS_DEBUG}" CACHE STRING
    "Flags used by the shared libraries linker during coverage builds."
    FORCE)
  mark_as_advanced(
    CMAKE_CXX_FLAGS_COVERAGE
    CMAKE_EXE_LINKER_FLAGS_COVERAGE
    CMAKE_SHARED_LINKER_FLAGS_COVERAGE)
  set(CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE}" CACHE STRING
    "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel Coverage."
    FORCE)

  add_cxx_compiler_flag(--coverage COVERAGE)
  find_program(GCOV gcov)
  find_program(LCOV lcov)
  find_program(GENHTML genhtml)
  find_program(CTEST ctest)
  if (GCOV AND LCOV AND GENHTML AND CTEST AND HAVE_CXX_FLAG_COVERAGE)
    add_custom_command(
      OUTPUT ${CMAKE_BINARY_DIR}/lcov/index.html
      COMMAND ${LCOV} -q -z -d .
      COMMAND ${LCOV} -q --no-external -c -b "${CMAKE_SOURCE_DIR}" -d . -o before.lcov -i
      COMMAND ${CTEST} --force-new-ctest-process
      COMMAND ${LCOV} -q --no-external -c -b "${CMAKE_SOURCE_DIR}" -d . -o after.lcov
      COMMAND ${LCOV} -q -a before.lcov -a after.lcov --output-file final.lcov
      COMMAND ${LCOV} -q -r final.lcov "'${CMAKE_SOURCE_DIR}/test/*'" -o final.lcov
      COMMAND ${GENHTML} final.lcov -o lcov --demangle-cpp --sort -p "${CMAKE_BINARY_DIR}" -t fd
      DEPENDS fd_test
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
      COMMENT "Running LCOV"
    )
    add_custom_target(coverage
      DEPENDS ${CMAKE_BINARY_DIR}/lcov/index.html
      COMMENT "LCOV report at lcov/index.html"
    )
    message(STATUS "Coverage command added")
  else()
    if (HAVE_CXX_FLAG_COVERAGE)
      set(CXX_FLAG_COVERAGE_MESSAGE supported)
    else()
      set(CXX_FLAG_COVERAGE_MESSAGE unavailable)
    endif()
    message(WARNING
      "Coverage not available:\n"
      "  gcov: ${GCOV}\n"
      "  lcov: ${LCOV}\n"
      "  genhtml: ${GENHTML}\n"
      "  ctest: ${CTEST}\n"
      "  --coverage flag: ${CXX_FLAG_COVERAGE_MESSAGE}")
  endif()
endif()

# benchmarks
IF(FD_BUILD_BENCHMARKS)
    # turn off test of google/benchmark
    option(BENCHMARK_ENABLE_TESTING "tests in google/benchmark off" OFF)
    ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/submodule/benchmark)
    ADD_SUBDIRECTORY(benchmarks)
ENDIF()

# examples
IF(FD_BUILD_EXAMPLES)
    ADD_SUBDIRECTORY(examples)
ENDIF()
