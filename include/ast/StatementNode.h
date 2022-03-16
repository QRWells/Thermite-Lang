/**
 * @file StatementNode.h
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
#ifndef THERMITE_LANG_AST_STATEMENTNODE
#define THERMITE_LANG_AST_STATEMENTNODE

#include <memory>
#include <string>
#include <utility>

#include <fmt/core.h>

#include "ast/AstNode.h"
#include "ast/ExpressionNode.h"

namespace thermite {
class VarDefStatement final : public StatementNode {
public:
  VarDefStatement(IdentifierExpr const &type, IdentifierExpr &id)
      : Type(type), Id(id), Assign(nullptr) {}

  VarDefStatement(IdentifierExpr const &type, IdentifierExpr &id,
                  ExpressionNode *statement)
      : Type(type), Id(id), Assign(statement) {}

  [[nodiscard]] auto codeGen(Generator &generator) -> llvm::Value * override;

private:
  IdentifierExpr const &Type;
  IdentifierExpr &Id;
  ExpressionNode *Assign;
};

class FuncSignature {
public:
  FuncSignature(std::string_view id, ParameterList parameters)
      : Id(id), Parameters(std::move(parameters)) {}
  auto codeGen(Generator &generator) -> llvm::Function *;
  auto getName() -> std::string;

private:
  std::string Id;
  ParameterList Parameters;
};

class FuncStatement final : public StatementNode {
public:
  FuncStatement(std::unique_ptr<FuncSignature> signature,
                std::unique_ptr<ExpressionNode> body)
      : Signature(std::move(signature)), Body(std::move(body)) {}

  [[nodiscard]] auto codeGen(Generator &generator) -> llvm::Value * override;

private:
  std::unique_ptr<FuncSignature> Signature;
  std::unique_ptr<ExpressionNode> Body;
};
} // namespace thermite

#endif // !THERMITE_LANG_AST_STATEMENTNODE
