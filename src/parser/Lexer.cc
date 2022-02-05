// Copyright (c) 2021 QRWells. All rights reserved.
// Licensed under the MIT license.
// See LICENSE file in the project root for full license information.
//
// This file is part of Project Thermite-Lang.
// File Name   : Lexer.cc
// Author      : QRWells
// Created at  : 2021/12/19 3:48
// Description :

#include "parser/Lexer.h"
#include "ast/AstNode.h"

#include <cctype>
#include <fstream>
#include <sstream>
#include <string>
#include <type_traits>

namespace thermite {
Lexer::Lexer(std::string_view const &code) : Code(code), Iter(Code.begin()) {}

Lexer::Lexer(std::ifstream const &file) {
  std::stringstream StringStream;
  StringStream << file.rdbuf();
  Code = StringStream.str();
  Iter = Code.begin();
}

auto Lexer::getToken() -> Token {
  // Ignore white spaces
  while (std::isspace(LastChar) != 0)
    fetchChar();

  // Get identifiers
  if (std::isalpha(LastChar) != 0 || LastChar == '_')
    return proceedIdentifier();

  // Get number
  if (std::isdigit(LastChar) != 0 || LastChar == '.')
    return proceedNumber();

  if (BinOperator.contains(LastChar))
    return proceedOperator();

  if (Bracket.contains(LastChar))
    return proceedBracket();

  // Ignore comments
  if (LastChar == '#') {
    do {
      fetchChar();
    } while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');
    if (LastChar != EOF)
      return getToken();
  }
  // End
  if (LastChar == EOF)
    return {TokenClass::Eof, ""};
  std::string Unknown{LastChar};
  fetchChar();
  return {TokenClass::Unknown, Unknown};
}

auto Lexer::fetchChar() -> void {
  if (Iter == Code.end()) {
    LastChar = EOF;
    return;
  }

  LastChar = *Iter++;
  ++Offset;

  if (LastChar == '\n') {
    ++LineNo;
    Offset = 0;
  }
}

auto Lexer::proceedIdentifier() -> Token {
  std::string IdentifierStr;
  do {
    IdentifierStr += LastChar;
    fetchChar();
  } while (std::isalnum(LastChar) != 0 || LastChar == '_');

  auto Keyword = KeyMap.find(IdentifierStr);
  if (Keyword != KeyMap.end())
    return {Keyword->second, IdentifierStr};

  return {TokenClass::Identifier, IdentifierStr};
}

auto Lexer::proceedNumber() -> Token {
  std::string NumStr;
  do {
    NumStr += LastChar;
    fetchChar();
  } while (std::isdigit(LastChar) != 0 || LastChar == '.');
  return {TokenClass::Number, NumStr};
}

auto Lexer::proceedBracket() -> Token {
  auto Res = Bracket.at(LastChar);
  auto Temp = LastChar;
  fetchChar();
  return {Res, std::string{Temp}};
}

auto Lexer::proceedOperator() -> Token {
  auto Temp = LastChar;
  std::string Result{Temp};
  fetchChar();
  if (LastChar == '=' && (Temp == '>' || Temp == '<' || Temp == '=')) {
    Result += LastChar;
    fetchChar();
  }
  return {TokenClass::BinOperator, Result};
}
} // namespace thermite
