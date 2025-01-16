file(GLOB_RECURSE sources CONFIGURE_DEPENDS
    src/*.c
    src/*.h
    include/*.h
)
find_library(LAB2_LIB lab2 PATHS /usr/local/lib)
if (NOT LAB2_LIB)
    message(FATAL_ERROR "Library lab2 not found!")
endif()
add_executable(lab1 ${sources})
target_link_libraries(lab1 PRIVATE ${LAB2_LIB})
target_include_directories(lab1 PRIVATE /usr/local/include)
target_include_directories(lab1 PRIVATE src include)
