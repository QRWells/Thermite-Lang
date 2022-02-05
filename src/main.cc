/**
 * @file main.cc
 * @author QRWells (qirui.wang@moegi.waseda.jp)
 * @brief
 * @version 0.1
 * @date 2022-01-03
 *
 * @copyright Copyright (c) 2021 QRWells. All rights reserved.
 * Licensed under the MIT license.
 *
 */

#include "parser/Lexer.h"
#include "parser/Token.h"

#include <fmt/core.h>
#include <fstream>
#include <iostream>
#include <string>

auto main(int argc, char *const argv[]) -> int {
  if (argc < 2)
    return -1;
  std::ifstream Code;
  Code.open(*(argv + 1));
  if (!Code.is_open())
    return -1;
  thermite::Lexer L(Code);
  auto Token = L.getToken();
  while (Token.getClass() != thermite::TokenClass::Eof) {
    fmt::print("{}\n", Token.toString());
    Token = L.getToken();
  }
  Code.close();
  return 0;
}