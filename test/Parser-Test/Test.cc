#include <iostream>
#include <memory>

#include "../Program/TestCases.h"
#include "parser/Lexer.h"
#include "parser/Parser.h"

using namespace std;

auto main(int argc, char *const argv[]) -> int {
  const auto *Code = PROG1;
  auto L = make_unique<thermite::Lexer>(Code);

  thermite::Parser P{move(L)};
  P.generate();

  return 0;
}