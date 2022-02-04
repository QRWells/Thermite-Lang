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
#include "parser/TokenClass.h"

#include <fstream>
#include <iostream>
#include <string>

auto main(int argc, char *const argv[]) -> int {
  std::ifstream Code;
  Code.open("/mnt/c/Users/wqrmc/Documents/GitHub/Thermite-Lang/test/test.tm");
  thermite::Lexer L(Code);
  thermite::TokenClass T(thermite::TokenClass::Eof);
  double Val = 0;
  std::string S;
  char C = 0;
  while (true) {
    T = L.getToken();
    if (T == thermite::TokenClass::Eof)
      break;
    std::cout << thermite::tokenToCstr(T) << " : ";
    if (T == thermite::TokenClass::Number) {
      Val = L.getNumber();
      std::cout << Val << std::endl;
      continue;
    }
    if (T == thermite::TokenClass::Unknown) {
      C = L.getUnknown();
      std::cout << C << std::endl;
      continue;
    }
    if (T == thermite::TokenClass::BinOperator) {
      std::cout << static_cast<char>(L.getBinOperator()) << std::endl;
      continue;
    }
    S = L.getIdentifier();
    std::cout << S << std::endl;
  }
  Code.close();
  return 0;
}