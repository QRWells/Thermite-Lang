/**
 * @file TokenClass.h
 * @author QRWells (qirui.wang@moegi.waseda.jp)
 * @brief
 * @version 0.1
 * @date 2022-02-05
 *
 * @copyright Copyright (c) 2021 QRWells. All rights reserved.
 * Licensed under the MIT license.
 *
 */

namespace thermite {
enum class TokenClass {
  Unknown,
  Eof,
  Identifier,
  Func,
  Number,
  Keyword,
  UnaryOperator,
  BinOperator,

  LeftParen,
  RightParen,
  LeftSqBra,
  RightSqBra,
  LeftCuBra,
  RightCuBra,

  SemiColon,
  Colon
};

constexpr auto tokenToCstr(TokenClass token) noexcept -> char const * {
  switch (token) {
  case TokenClass::Eof:
    return "EOF";
  case TokenClass::Unknown:
    return "Unknown";
  case TokenClass::Identifier:
    return "Identifier";
  case TokenClass::Func:
    return "Func";
  case TokenClass::Number:
    return "Number";
  case TokenClass::Keyword:
    return "Keyword";
  case TokenClass::UnaryOperator:
    return "UnaryOperator";
  case TokenClass::BinOperator:
    return "BinaryOperator";
  case TokenClass::LeftParen:
    return "LeftParen";
  case TokenClass::RightParen:
    return "RightParen";
  case TokenClass::LeftSqBra:
    return "LeftSqBra";
  case TokenClass::RightSqBra:
    return "RightSqBra";
  case TokenClass::LeftCuBra:
    return "LeftCuBra";
  case TokenClass::RightCuBra:
    return "RightCuBra";
  case TokenClass::SemiColon:
    return "SemiColon";
  case TokenClass::Colon:
    return "Colon";
  }
}
} // namespace thermite