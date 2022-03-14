#pragma once
#ifndef THERMITE_LANG_PARSER_TOKEN
#define THERMITE_LANG_PARSER_TOKEN

#include "ast/AstNode.h"
#include "enum/TokenClass.h"
#include <fmt/core.h>
#include <string>

namespace thermite {
class Token {
public:
  Token() = default;
  Token(TokenClass tokenClass, std::string_view value)
      : TokenClass(tokenClass), Value(value) {}
  [[nodiscard]] auto getNumber() const -> double;
  [[nodiscard]] auto getString() const -> std::string;
  [[nodiscard]] auto getClass() const -> enum TokenClass;
  [[nodiscard]] auto getOperator() const -> enum BinaryOperation;
  [[nodiscard]] auto toString() const -> std::string;

  auto operator==(TokenClass const &tokenClass) -> bool;
  friend auto operator<<(std::ostream &output, const Token &token)
      -> std::ostream &;

private:
  TokenClass TokenClass{};
  std::string Value;
};

} // namespace thermite

#endif