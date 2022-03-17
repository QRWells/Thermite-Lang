cmake_minimum_required (VERSION 3.21)

find_package(fmt)
find_package(LLVM 13.0 REQUIRED CONFIG)

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_executable(Lexer-Test
        "Lexer-Test/Test.cc"
)

add_executable(Parser-Test
        "Parser-Test/Test.cc"
)

llvm_map_components_to_libnames(llvm_libs support core irreader)
target_link_libraries(Thermite_Lang ${llvm_libs})

target_link_libraries(Thermite_Lang fmt::fmt)
