/**
 * @file ExpressionNode.cc
 * @author QRWells (qirui.wang@moegi.waseda.jp)
 * @brief
 * @version 0.1
 * @date 2021-12-19
 *
 * @copyright Copyright (c) 2021 QRWells. All rights reserved.
 * Licensed under the MIT license.
 *
 */

#include "ast/ExpressionNode.h"

namespace thermite {
auto IntegerExpr::codeGen(const CodeGenContext &context) -> llvm::Value * {
  return AstNode::codeGen(context);
}

auto DoubleExpr::codeGen(const CodeGenContext &context) -> llvm::Value * {
  return AstNode::codeGen(context);
}

auto IdentifierExpr::codeGen(const CodeGenContext &context) -> llvm::Value * {
  return AstNode::codeGen(context);
}
auto UnaryOpExpr::codeGen(const CodeGenContext &context) -> llvm::Value * {
  return AstNode::codeGen(context);
}
auto BinaryOpExpr::codeGen(const CodeGenContext &context) -> llvm::Value * {
  return AstNode::codeGen(context);
}
auto CallExpr::codeGen(const CodeGenContext &context) -> llvm::Value * {
  return AstNode::codeGen(context);
}
auto AssignExpr::codeGen(const CodeGenContext &context) -> llvm::Value * {
  return AstNode::codeGen(context);
}
} // namespace thermite