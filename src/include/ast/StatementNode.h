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
#include <memory>
#ifndef THERMITE_LANG_AST_STATEMENTNODE
#define THERMITE_LANG_AST_STATEMENTNODE

#include <utility>

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

  [[nodiscard]] auto codeGen(CodeGenContext const &context)
      -> llvm::Value * override;

private:
  IdentifierExpr const &Type;
  IdentifierExpr &Id;
  ExpressionNode *Assign;
};

class FuncSignature {
public:
  FuncSignature(IdentifierExpr const &id, ParameterList parameters)
      : Id(id), Parameters(std::move(parameters)) {}

private:
  IdentifierExpr const &Id;
  ParameterList Parameters;
};

class FuncStatement final : public StatementNode {
public:
  FuncStatement(std::unique_ptr<FuncSignature> signature,
                std::unique_ptr<ExpressionNode> body)
      : Signature(std::move(signature)), Body(std::move(body)) {}

  [[nodiscard]] auto codeGen(CodeGenContext const &context)
      -> llvm::Value * override;

private:
  std::unique_ptr<FuncSignature> Signature;
  std::unique_ptr<ExpressionNode> Body;
};
} // namespace thermite

#endif // !THERMITE_LANG_AST_STATEMENTNODE
