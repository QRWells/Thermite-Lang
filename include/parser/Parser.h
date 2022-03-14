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
#include "ast/AstNode.h"
#include "ast/StatementNode.h"
#ifndef THERMITE_LANG_PARSER
#define THERMITE_LANG_PARSER

#include <memory>
#include <unordered_map>
#include <vector>

#include "ast/ExpressionNode.h"
#include "enum/Operation.h"
#include "parser/Lexer.h"
#include "parser/Token.h"

namespace thermite {
class Parser {
public:
  Parser() = default;
  ~Parser() = default;

  [[nodiscard]] auto parse(std::vector<Token> const &)
      -> std::unique_ptr<AstNode>;

private:
  std::unique_ptr<Lexer> Lexer;
  std::unordered_map<std::string, std::unique_ptr<IdentifierExpr>> Variables;
  std::unordered_map<std::string, std::unique_ptr<IdentifierExpr>> Functions;
  Token CurrentToken;

  const std::unordered_map<BinaryOperation, int> BinOperatorPrecedence = {
      {BinaryOperation::Multiply, 20},  {BinaryOperation::Divide, 20},
      {BinaryOperation::Remain, 20},    {BinaryOperation::Add, 10},
      {BinaryOperation::Substract, 10}, {BinaryOperation::GreaterThan, 5},
      {BinaryOperation::LessThan, 5},   {BinaryOperation::Equal, 4},
      {BinaryOperation::NotEqual, 4},   {BinaryOperation::And, 3},
      {BinaryOperation::Xor, 2},        {BinaryOperation::Or, 1}};

  [[nodiscard]] auto parseNumberExpr() -> std::unique_ptr<ExpressionNode>;
  [[nodiscard]] auto parseParenExpr() -> std::unique_ptr<ExpressionNode>;
  [[nodiscard]] auto parseBlockState() -> std::unique_ptr<ExpressionNode>;
  [[nodiscard]] auto parseIdentifierExpr() -> std::unique_ptr<ExpressionNode>;
  [[nodiscard]] auto parsePrimary() -> std::unique_ptr<ExpressionNode>;
  [[nodiscard]] auto parseExpression() -> std::unique_ptr<ExpressionNode>;
  [[nodiscard]] auto parseBinOpRhs(int minPrecedence,
                                   std::unique_ptr<ExpressionNode> lhs)
      -> std::unique_ptr<ExpressionNode>;
  [[nodiscard]] auto parseFuncSignature() -> std::unique_ptr<FuncSignature>;
  [[nodiscard]] auto parseFuncDef() -> std::unique_ptr<FuncStatement>;
  [[nodiscard]] auto parseTopFunc() -> std::unique_ptr<FuncStatement>;

  auto getNextToken() -> void;
  [[nodiscard]] auto getOperatorPrecedence() const -> int;
};
} // namespace thermite
#endif
