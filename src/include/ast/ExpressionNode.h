/**
 * @file ExpressionNode.h
 * @author QRWells (qirui.wang@moegi.waseda.jp)
 * @brief
 * @version 0.1
 * @date 2021-12-19
 *
 * @copyright Copyright (c) 2021 QRWells. All rights reserved.
 * Licensed under the MIT license.
 *
 */

#pragma once

#include <memory>

#ifndef THERMITE_LANG_AST_EXPRAST
#define THERMITE_LANG_AST_EXPRAST

#include "AstNode.h"

namespace thermite {
class IntegerExpr final : public ExpressionNode {
public:
  explicit IntegerExpr(int64_t const &val) : Val(val) {}
  [[nodiscard]] auto codeGen(CodeGenContext const &context)
  -> llvm::Value * override;

private:
  int64_t Val;
};

class DoubleExpr final : public ExpressionNode {
public:
  explicit DoubleExpr(double const &val) : Val(val) {}
  [[nodiscard]] auto codeGen(CodeGenContext const &context)
  -> llvm::Value * override;

private:
  double Val;
};

class IdentifierExpr final : public ExpressionNode {
public:
  explicit IdentifierExpr(std::string_view const name) : Name(name) {}
  [[nodiscard]] auto codeGen(CodeGenContext const &context)
  -> llvm::Value * override;

private:
  std::string Name;
};

class UnaryOpExpr final : public ExpressionNode {
public:
  UnaryOpExpr(UnaryOperation const op, ExpressionNode &rhs)
      : Op(op), Rhs(rhs) {}

  [[nodiscard]] auto codeGen(CodeGenContext const &context)
  -> llvm::Value * override;

private:
  UnaryOperation Op;
  ExpressionNode &Rhs;
};

class BinaryOpExpr final : public ExpressionNode {
public:
  BinaryOpExpr(BinaryOperation const &op, std::unique_ptr<ExpressionNode> lhs,
               std::unique_ptr<ExpressionNode> rhs)
      : Op(op), Lhs(std::move(lhs)), Rhs(std::move(rhs)) {}

  [[nodiscard]] auto codeGen(CodeGenContext const &context)
  -> llvm::Value * override;

private:
  BinaryOperation Op;
  std::unique_ptr<ExpressionNode> Lhs, Rhs;
};

class CallExpr final : public ExpressionNode {
public:
  explicit CallExpr(std::string_view id) : Id(id) {}

  CallExpr(std::string_view id, ArgumentList arguments)
      : Id(id), Arguments(std::move(arguments)) {}

  [[nodiscard]] auto codeGen(CodeGenContext const &context)
  -> llvm::Value * override;

private:
  std::string Id;
  ArgumentList Arguments;
};

class AssignExpr final : public ExpressionNode {
public:
  AssignExpr(std::string_view lhs, ExpressionNode &rhs) : Lhs(lhs), Rhs(rhs) {}

  [[nodiscard]] auto codeGen(CodeGenContext const &context)
  -> llvm::Value * override;

private:
  std::string Lhs;
  ExpressionNode &Rhs;
};
} // namespace thermite
#endif // !THERMITE_LANG_AST_EXPRAST
