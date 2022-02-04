// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Thermite-Lang.
// File Name   : Lexer.h
// Author      : QRWells
// Created at  : 2021/12/19 3:48
// Description :

#pragma once
#include "ast/AstNode.h"
#include <cstddef>
#include <fstream>
#include <set>
#include <unordered_map>
#include <vector>
#ifndef THERMITE_LANG_LEXER
#define THERMITE_LANG_LEXER

#include <string>
#include <string_view>

#include "ast/ExpressionNode.h"
#include "parser/Token.h"

namespace thermite {
class Lexer {
public:
  explicit Lexer(std::string_view const &code);
  Lexer(std::ifstream const &file);
  ~Lexer() = default;

  [[nodiscard]] auto getToken() -> TokenClass;
  [[nodiscard]] auto getNumber() const -> double;
  [[nodiscard]] auto getIdentifier() const -> std::string;
  [[nodiscard]] auto getUnknown() const -> char;
  [[nodiscard]] auto getBinOperator() const -> BinaryOperation;

private:
  std::string Code;
  std::string IdentifierStr;
  BinaryOperation BinaryOperator = BinaryOperation::Add;
  char LastChar = ' ';

  const std::unordered_map<std::string, TokenClass> KeyMap = {
      {"for", TokenClass::Keyword},
      {"if", TokenClass::Keyword},
      {"then", TokenClass::Keyword},
      {"else", TokenClass::Keyword},
      {"func", TokenClass::Func}};

  const std::set<char> BinOperator = {'+', '-', '*', '/', '%', '|',
                                      '^', '&', '>', '<', '='};

  const std::unordered_map<char, TokenClass> Bracket = {
      {'(', TokenClass::LeftParen}, {')', TokenClass::RightParen},
      {'[', TokenClass::LeftSqBra}, {']', TokenClass::RightSqBra},
      {'{', TokenClass::LeftCuBra}, {'}', TokenClass::RightCuBra},
  };

  double NumberVal = 0;
  std::basic_string<char>::iterator Iter;
  size_t LineNo = 1;
  size_t Offset = 0;
  char Unknown = 0;

  auto fetchChar() -> void;
  auto proceedNumber() -> TokenClass;
  auto proceedIdentifier() -> TokenClass;
  auto proceedBracket() -> TokenClass;
  auto proceedOperator() -> TokenClass;
};
} // namespace thermite
#endif
