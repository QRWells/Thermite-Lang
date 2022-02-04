// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Thermite-Lang.
// File Name   : Parser.cc
// Author      : QRWells
// Created at  : 2021/12/19 3:57
// Description :

#include "parser/Parser.h"
#include "ast/ExpressionNode.h"
#include "parser/Token.h"
#include <memory>

namespace thermite {
auto Parser::parse(const std::vector<Token> &tokenList)
    -> std::unique_ptr<AstNode> {
  return {};
}

auto Parser::parseNumberExpr() -> std::unique_ptr<AstNode> {
  auto Result = std::make_unique<DoubleExpr>(Lexer->getNumber());
  getNextToken();
  return std::move(Result);
}

auto Parser::parseParenExpr() -> std::unique_ptr<AstNode> {
  getNextToken();
  auto Expr = parseExpression();
  getNextToken();
  return Expr;
}

auto Parser::parseBlockState() -> std::unique_ptr<AstNode> {
  getNextToken();
  auto Expr = parseExpression();
  getNextToken();
  return Expr;
}

auto Parser::parseIdentifierExpr() -> std::unique_ptr<AstNode> {
  auto Id = Lexer->getIdentifier();
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

  return nullptr;
}

auto Parser::getNextToken() -> void { CurrentToken = Lexer->getToken(); }

auto Parser::parsePrimary() -> std::unique_ptr<AstNode> {
  switch (CurrentToken) {
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

} // namespace thermite