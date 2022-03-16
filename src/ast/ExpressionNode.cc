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

#include <llvm/ADT/APFloat.h>
#include <llvm/IR/Constants.h>

#include "ast/AstNode.h"
#include "ast/ExpressionNode.h"
#include "enum/Operation.h"
#include "parser/Generator.h"

namespace thermite {
auto IntegerExpr::codeGen(Generator &generator) -> llvm::Value * {
  return nullptr;
}

auto DoubleExpr::codeGen(Generator &generator) -> llvm::Value * {
  return llvm::ConstantFP::get(generator.getContext(), llvm::APFloat(Val));
}

auto IdentifierExpr::codeGen(Generator &generator) -> llvm::Value * {
  return generator.getNamedValues().at(Name);
}
auto UnaryOpExpr::codeGen(Generator &generator) -> llvm::Value * {
  return nullptr;
}
auto BinaryOpExpr::codeGen(Generator &generator) -> llvm::Value * {
  auto *TLhs = Lhs->codeGen(generator);
  auto *TRhs = Rhs->codeGen(generator);
  switch (Op) {
  case BinaryOperation::Add:
    return generator.getIrBuilder().CreateFAdd(TLhs, TRhs, "addtmp");
  default:
    return nullptr;
  }
}

auto CallExpr::codeGen(Generator &generator) -> llvm::Value * {
  auto *Callee = generator.getModule().getFunction(Id);
  std::vector<llvm::Value *> Args;
  for (auto const &ArgExpr : Arguments)
    Args.push_back(ArgExpr->codeGen(generator));

  return generator.getIrBuilder().CreateCall(Callee, Args, "calltmp");
}

auto AssignExpr::codeGen(Generator &generator) -> llvm::Value * {
  return nullptr;
}

} // namespace thermite