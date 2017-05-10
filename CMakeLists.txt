cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(MacSTL)

include(FeatureSummary)

include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/macstl ${CMAKE_SOURCE_DIR}/test)
add_definitions("-DUSE_REALTIMER")

MACRO(INSTALL_HEADERS_WITH_DIRECTORY HEADER_LIST)
    FOREACH(HEADER ${${HEADER_LIST}})
        STRING(REGEX MATCH "(.\\\*)\\\[/\\\]" DIR ${HEADER})
        INSTALL(FILES ${HEADER} DESTINATION include/${DIR})
    ENDFOREACH(HEADER)
ENDMACRO(INSTALL_HEADERS_WITH_DIRECTORY)

install_headers_with_directory(${CMAKE_SOURCE_DIR}/macstl)

set(TESTS benchmark
    benchmark-macstl2
    benchmark-macstl
    exhaustive
    findtest
    mmaptest
    vectest
)
if(APPLE)
    set(TESTS ${TESTS}
        comtest
        coretest
        machtest
    )
endif()

foreach(T ${TESTS})
    add_executable(${T} ${CMAKE_SOURCE_DIR}/test/${T}.cpp)
endforeach(T ${TESTS})

FEATURE_SUMMARY(WHAT ALL)
