CMAKE_MINIMUM_REQUIRED(VERSION 3.2)

PROJECT(test_teich)

ADD_EXECUTABLE(
    test_teich
    source/test_teich_main.cpp
    source/test_teich_leb128_unsigned_decode.cpp
)

INCLUDE_DIRECTORIES(
    test_teich
    dependencies/Catch/single_include
    dependencies/libbitter/include
    ../include
)

# Add C++14 support
TARGET_COMPILE_FEATURES(
    test_teich
    PRIVATE
    cxx_relaxed_constexpr
)

SET_PROPERTY(
    TARGET test_teich
    APPEND_STRING PROPERTY COMPILE_FLAGS
    "-Wall -Werror"
)

IF(NOT WIN32)
    TARGET_LINK_LIBRARIES(
        test_teich
        gcov asan
    )

    SET_PROPERTY(
        TARGET test_teich
        APPEND_STRING PROPERTY COMPILE_FLAGS
        " -fsanitize=address --coverage"
    )
ENDIF()

