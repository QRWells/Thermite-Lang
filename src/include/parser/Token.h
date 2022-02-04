#pragma once
#ifndef THERMITE_LANG_PARSER_TOKEN
#define THERMITE_LANG_PARSER_TOKEN

#include <fmt/core.h>
#include <string>

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

  Comma,
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
  case TokenClass::Comma:
    return "Comma";
  case TokenClass::Colon:
    return "Colon";
  }
}

class Token {
public:
  explicit Token(TokenClass tokenClass, std::string_view value)
      : TokenClass(tokenClass), Value(value) {}

private:
  inline auto toString() -> std::string {
    return fmt::format("{{Token: {}, Value: {}}}", tokenToCstr(TokenClass),
                       Value);
  }
  TokenClass TokenClass;
  std::string Value;
};

} // namespace thermite

#endif