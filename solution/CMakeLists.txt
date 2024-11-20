file(GLOB_RECURSE sources CONFIGURE_DEPENDS
    src/*.c
    src/*.h
    include/*.h
)

add_executable(shell ${sources})
target_include_directories(shell PRIVATE src include)
