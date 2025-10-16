function(setup_compiler_flags target)
  target_compile_options(
    ${target}
    PRIVATE $<$<CONFIG:Debug>:
            -O0
            -Wall
            -Werror
            -Wextra
            -Wpedantic
            -Wconversion
            -Wcast-align
            -Wunused
            -Wshadow
            -Wold-style-cast
            -Wuninitialized
            -Woverloaded-virtual
            -Wsign-conversion
            -fno-inline
            >)
endfunction()

function(setup_compiler_flags_interface target)
  target_compile_options(
    ${target}
    INTERFACE $<$<CONFIG:Debug>:
              -O0
              -Wall
              -Werror
              -Wextra
              -Wpedantic
              -Wconversion
              -Wcast-align
              -Wunused
              -Wshadow
              -Wold-style-cast
              -Wuninitialized
              -Woverloaded-virtual
              -Wsign-conversion
              -fno-inline
              >)
endfunction()
