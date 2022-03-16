cmake_minimum_required (VERSION 3.21)

find_package(BISON)
find_package(FLEX)
find_package(fmt)
find_package(LLVM 13.0 REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_executable(Thermite_Lang
        "main.cc"
        "parser/Token.cc"
        "parser/Lexer.cc"
        "parser/Parser.cc"
        "parser/Generator.cc" 
        "ast/AstNode.cc"
        "ast/ExpressionNode.cc"
        "ast/StatementNode.cc"
)

llvm_map_components_to_libnames(llvm_libs support core irreader)
target_link_libraries(Thermite_Lang ${llvm_libs})

target_link_libraries(Thermite_Lang fmt::fmt)
