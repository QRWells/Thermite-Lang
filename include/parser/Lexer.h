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
#ifndef THERMITE_LANG_LEXER
#define THERMITE_LANG_LEXER

#include <cstddef>
#include <fstream>
#include <set>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "ast/AstNode.h"
#include "ast/ExpressionNode.h"
#include "parser/Token.h"

namespace thermite {
class Lexer {
public:
  explicit Lexer(std::string_view const &code);
  Lexer(std::ifstream const &file);
  ~Lexer() = default;

  [[nodiscard]] auto getToken() -> Token;

private:
  std::string Code;
  char LastChar = ' ';

  const std::unordered_map<std::string, TokenClass> KeyMap = {
      {"for", TokenClass::Keyword},  {"while", TokenClass::Keyword},
      {"if", TokenClass::Keyword},   {"then", TokenClass::Keyword},
      {"else", TokenClass::Keyword}, {"func", TokenClass::Func}};

  const std::set<char> BinOperator = {'+', '-', '*', '/', '%', '|',
                                      '^', '&', '>', '<', '=', '!'};

  const std::unordered_map<char, TokenClass> Bracket = {
      {'(', TokenClass::LeftParen}, {')', TokenClass::RightParen},
      {'[', TokenClass::LeftSqBra}, {']', TokenClass::RightSqBra},
      {'{', TokenClass::LeftCuBra}, {'}', TokenClass::RightCuBra},
  };

  std::basic_string<char>::iterator Iter;
  size_t LineNo = 1;
  size_t Offset = 0;

  auto fetchChar() -> void;
  auto proceedNumber() -> Token;
  auto proceedIdentifier() -> Token;
  auto proceedBracket() -> Token;
  auto proceedOperator() -> Token;
};
} // namespace thermite
#endif
