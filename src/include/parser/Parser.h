// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Thermite-Lang.
// File Name   : Parser.h
// Author      : QRWells
// Created at  : 2021/12/19 3:57
// Description :

#pragma once
#include "parser/Token.h"
#include <memory>
#ifndef THERMITE_LANG_PARSER
#define THERMITE_LANG_PARSER

#include <unordered_map>
#include <vector>

#include "ast/ExpressionNode.h"
#include "parser/Lexer.h"

namespace thermite {
class Parser {
public:
  Parser() = default;
  ~Parser() = default;

  [[nodiscard]] auto parse(std::vector<Token> const &)
      -> std::unique_ptr<AstNode>;

private:
  std::unique_ptr<Lexer> Lexer;
  std::unordered_map<std::string, IdentifierExpr> Variables;

  TokenClass CurrentToken = TokenClass::Unknown;
  [[nodiscard]] auto parseNumberExpr() -> std::unique_ptr<AstNode>;
  [[nodiscard]] auto parseParenExpr() -> std::unique_ptr<AstNode>;
  [[nodiscard]] auto parseBlockState() -> std::unique_ptr<AstNode>;
  [[nodiscard]] auto parseIdentifierExpr() -> std::unique_ptr<AstNode>;
  [[nodiscard]] auto parsePrimary() -> std::unique_ptr<AstNode>;
  [[nodiscard]] auto parseExpression() -> std::unique_ptr<ExpressionNode>;

  auto getNextToken() -> void;
};
} // namespace thermite
#endif
