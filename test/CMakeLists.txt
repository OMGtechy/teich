CMAKE_MINIMUM_REQUIRED(VERSION 3.2)

PROJECT(test_teich)

ADD_EXECUTABLE(
    test_teich
    source/test_teich_main.cpp
    source/test_teich_leb128_unsigned_decode.cpp
    source/test_teich_leb128_unsigned_encode.cpp
)

INCLUDE_DIRECTORIES(
    test_teich
    dependencies/Catch/single_include
    dependencies/libbitter/include
    ../include
)

IF(NOT WIN32)
    # Add C++14 support
    TARGET_COMPILE_FEATURES(
        test_teich
        PRIVATE
        cxx_relaxed_constexpr
    )

	TARGET_LINK_LIBRARIES(
        test_teich
        gcov asan
    )

    SET_PROPERTY(
        TARGET test_teich
        APPEND_STRING PROPERTY COMPILE_FLAGS
        " -Wall -Werror -fsanitize=address --coverage"
    )
ENDIF()

