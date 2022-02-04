/**
 * @file AstNode.h
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
#ifndef THERMITE_LANG_AST_ASTNODE
#define THERMITE_LANG_AST_ASTNODE

#include "ast/CodeGenContext.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/GVN.h"

namespace thermite {

class AstNode {
public:
  virtual ~AstNode() = default;
  [[nodiscard]] virtual auto codeGen(const CodeGenContext &) -> llvm::Value *;
};

class StatementNode : public AstNode {};
class ExpressionNode : public AstNode {};
class VarDefStatement;

using StatementList = std::vector<std::unique_ptr<StatementNode>>;
using ExpressionList = std::vector<ExpressionNode *>;
using ParameterList = std::vector<VarDefStatement *>;
using ArgumentList = std::vector<std::unique_ptr<ExpressionNode>>;

enum class UnaryOperation {
  Minus,
  LogicNot,
};

enum class BinaryOperation : char {
  /**
   * @brief Math operation
   *
   */
  Add = '+',
  Substract = '-',
  Multiply = '*',
  Divide = '/',
  Remain = '%',

  LessThan = '<',
  GreaterThan = '>',
  Assign = '=',

  LessEqual = '<' + 20,
  GreatEqual = '>' + 20,
  Equal = '=' + 20,

  /**
   * @brief Boolean operation
   *
   */
  And = '&',
  Or = '|',
  Xor = '^',

  /**
   * @brief Logic operation
   *
   */
  LogicAnd,
  LogicOr
};
} // namespace thermite

#endif // !THERMITE_LANG_AST_ASTNODE
