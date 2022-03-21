// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Thermite-Lang.
// File Name   : Parser.cc
// Author      : QRWells
// Created at  : 2021/12/19 3:57
// Description :

#include <iostream>
#include <memory>
#include <ostream>
#include <utility>

#include <llvm/Support/raw_ostream.h>

#include <fmt/color.h>
#include <fmt/core.h>

#include "ast/AstNode.h"
#include "ast/ExpressionNode.h"
#include "ast/StatementNode.h"
#include "parser/Generator.h"
#include "parser/Parser.h"
#include "parser/Token.h"

namespace thermite {
auto Parser::generate(llvm::raw_ostream &output) -> int {
  if (Lexer == nullptr)
    fmt::print(stderr, fmt::fg(fmt::color::red), "No lexer was provided!");
  Generator G;
  getNextToken();
  while (true) {
    switch (CurrentToken.getClass()) {
    case TokenClass::Eof:
      return -1;
    case TokenClass::Func:
      parseFuncDef()->codeGen(G)->print(output);
      break;
    default:
      parseTopFunc()->codeGen(G)->print(output);
      break;
    }
  }
  return 0;
}

auto Parser::parseNumberExpr() -> std::unique_ptr<ExpressionNode> {
  auto Result = std::make_unique<DoubleExpr>(CurrentToken.getNumber());
  getNextToken();
  return std::move(Result);
}

auto Parser::parseParenExpr() -> std::unique_ptr<ExpressionNode> {
  getNextToken();
  auto Expr = parseExpression();
  getNextToken();
  return Expr;
}

auto Parser::parseBlockState() -> std::unique_ptr<ExpressionNode> {
  getNextToken();
  auto Expr = parseExpression();
  getNextToken();
  return Expr;
}

auto Parser::parseIdentifierExpr() -> std::unique_ptr<ExpressionNode> {
  auto Id = CurrentToken.getString();
  getNextToken();
  if (CurrentToken != TokenClass::LeftParen) {
    return std::make_unique<IdentifierExpr>(Id);
  }
  getNextToken();
  ArgumentList Args;
  while (CurrentToken != TokenClass::RightParen) {
    Args.push_back(parseExpression());
    if (CurrentToken == TokenClass::RightParen)
      break;
    getNextToken();
  }
  getNextToken();
  return std::make_unique<CallExpr>(Id, std::move(Args));
}

auto Parser::parseExpression() -> std::unique_ptr<ExpressionNode> {
  auto Lhs = parsePrimary();
  return parseBinOpRhs(0, std::move(Lhs));
}

auto Parser::getNextToken() -> void { CurrentToken = Lexer->getToken(); }

auto Parser::parsePrimary() -> std::unique_ptr<ExpressionNode> {
  switch (CurrentToken.getClass()) {
  case TokenClass::Identifier:
    return parseIdentifierExpr();
  case TokenClass::Number:
    return parseNumberExpr();
  case TokenClass::LeftParen:
    return parseParenExpr();
  default:
    return nullptr;
  }
}

auto Parser::getOperatorPrecedence() const -> int {
  if (BinOperatorPrecedence.contains(CurrentToken.getOperator()))
    return BinOperatorPrecedence.at(CurrentToken.getOperator());
  return -1;
}

auto Parser::parseBinOpRhs(int minPrecedence,
                           std::unique_ptr<ExpressionNode> lhs)
    -> std::unique_ptr<ExpressionNode> {
  while (true) {
    auto CurrentPrecedence = getOperatorPrecedence();
    if (CurrentPrecedence < minPrecedence)
      return lhs;
    auto Op = CurrentToken.getOperator();
    getNextToken();
    auto Rhs = parsePrimary();

    auto NextPrecedence = getOperatorPrecedence();
    if (CurrentPrecedence < NextPrecedence)
      Rhs = parseBinOpRhs(CurrentPrecedence + 1, std::move(Rhs));
    lhs = std::make_unique<BinaryOpExpr>(Op, std::move(lhs), std::move(Rhs));
  }
}

auto Parser::parseFuncSignature() -> std::unique_ptr<FuncSignature> {
  auto FunctionName = CurrentToken.getString();
  getNextToken(); // eat (
  ParameterList Parameters;
  getNextToken();
  while (CurrentToken.getClass() == TokenClass::Identifier) {
    Parameters.push_back(CurrentToken.getString());
    getNextToken();
  }
  getNextToken(); // eat )
  return std::make_unique<FuncSignature>(FunctionName, std::move(Parameters));
}
auto Parser::parseFuncDef() -> std::unique_ptr<FuncStatement> {
  getNextToken(); // eat def
  auto Proto = parseFuncSignature();
  auto Expr = parseExpression();
  return std::make_unique<FuncStatement>(std::move(Proto), std::move(Expr));
}
auto Parser::parseTopFunc() -> std::unique_ptr<FuncStatement> {
  auto Expr = parseExpression();
  auto Proto =
      std::make_unique<FuncSignature>("__main__", std::vector<std::string>());
  return std::make_unique<FuncStatement>(std::move(Proto), std::move(Expr));
}
} // namespace thermite