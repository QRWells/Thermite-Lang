#include <fstream>
#include <iostream>
#include <string>

#include <fmt/core.h>

#include "../Program/TestCases.h"
#include "parser/Lexer.h"
#include "parser/Token.h"

auto main(int argc, char *const argv[]) -> int {
  const auto *Code = PROG1;
  thermite::Lexer L(Code);
  auto Token = L.getToken();
  while (Token.getClass() != thermite::TokenClass::Eof) {
    fmt::print("{}\n", Token.toString());
    Token = L.getToken();
  }
  return 0;
}