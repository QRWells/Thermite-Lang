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

#include <llvm-13/llvm/ADT/APInt.h>
#include <llvm/ADT/APFloat.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Type.h>

#include "ast/AstNode.h"
#include "ast/ExpressionNode.h"
#include "enum/Operation.h"
#include "parser/Generator.h"

namespace thermite {
auto IntegerExpr::codeGen(Generator &generator) -> llvm::Value * {
  return llvm::ConstantInt::get(generator.getContext(), llvm::APInt(64, Val));
}

auto DoubleExpr::codeGen(Generator &generator) -> llvm::Value * {
  return llvm::ConstantFP::get(generator.getContext(), llvm::APFloat(Val));
}

auto IdentifierExpr::codeGen(Generator &generator) -> llvm::Value * {
  return generator.getNamedValues().at(Name);
}
auto UnaryOpExpr::codeGen(Generator &generator) -> llvm::Value * {
  auto *TRhs = Rhs.codeGen(generator);
  auto &IrBuilder = generator.getIrBuilder();
  auto &Context = generator.getContext();

  switch (Op) {
  case UnaryOperation::Minus:
    return IrBuilder.CreateFNeg(TRhs, "negtmp");
    // TODO : case UnaryOperation::LogicNot:
  }
  return nullptr;
}
auto BinaryOpExpr::codeGen(Generator &generator) -> llvm::Value * {
  auto *TLhs = Lhs->codeGen(generator);
  auto *TRhs = Rhs->codeGen(generator);
  auto &IrBuilder = generator.getIrBuilder();
  auto &Context = generator.getContext();

  llvm::Value *F = nullptr;
  switch (Op) {
    // computations
  case BinaryOperation::Add:
    return IrBuilder.CreateFAdd(TLhs, TRhs, "addtmp");
  case BinaryOperation::Substract:
    return IrBuilder.CreateFSub(TLhs, TRhs, "subtmp");
  case BinaryOperation::Multiply:
    return IrBuilder.CreateFMul(TLhs, TRhs, "multmp");
  case BinaryOperation::Divide:
    return IrBuilder.CreateFDiv(TLhs, TRhs, "divtmp");
  case BinaryOperation::Remain:
    return IrBuilder.CreateFRem(TLhs, TRhs, "remtmp");

    // comparasions
  case BinaryOperation::Equal:
    F = IrBuilder.CreateFCmpULT(TLhs, TRhs, "eqtmp");
    break;
  case BinaryOperation::NotEqual:
    F = IrBuilder.CreateFCmpUNE(TLhs, TRhs, "neqtmp");
    break;
  case BinaryOperation::GreaterThan:
    F = IrBuilder.CreateFCmpUGT(TLhs, TRhs, "getmp");
    break;
  case BinaryOperation::LessThan:
    F = IrBuilder.CreateFCmpULT(TLhs, TRhs, "getmp");
    break;
  case BinaryOperation::GreatEqual:
    F = IrBuilder.CreateFCmpUGE(TLhs, TRhs, "getmp");
    break;
  case BinaryOperation::LessEqual:
    F = IrBuilder.CreateFCmpULE(TLhs, TRhs, "getmp");
    break;
    // TODO: integer (logic ops)
    // TODO: assign
  default:
    return F;
  }
  return IrBuilder.CreateUIToFP(F, llvm::Type::getDoubleTy(Context));
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