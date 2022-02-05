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
        "include/parser/Token.h" "parser/Token.cc"
        "include/parser/Lexer.h" "parser/Lexer.cc"
        "include/parser/Parser.h" "parser/Parser.cc"
        "include/parser/Generator.h" "parser/Generator.cc" 
        "include/ast/AstNode.h" "ast/AstNode.cc"
        "include/ast/CodeGenContext.h" "ast/CodeGenContext.cc"
        "include/ast/ExpressionNode.h" "ast/ExpressionNode.cc"
        "include/ast/StatementNode.h" "ast/StatementNode.cc"
)

llvm_map_components_to_libnames(llvm_libs support core irreader)
target_link_libraries(Thermite_Lang ${llvm_libs})

target_link_libraries(Thermite_Lang fmt::fmt)
