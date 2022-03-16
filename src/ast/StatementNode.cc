/**
 * @file StatementNode.cc
 * @author QRWells (qirui.wang@moegi.waseda.jp)
 * @brief
 * @version 0.1
 * @date 2021-12-19
 *
 * @copyright Copyright (c) 2021 QRWells. All rights reserved.
 * Licensed under the MIT license.
 *
 */

#include "ast/StatementNode.h"
#include "ast/AstNode.h"

namespace thermite {
auto VarDefStatement::codeGen(Generator &generator) -> llvm::Value * {
  return nullptr;
}

auto FuncSignature::codeGen(Generator &generator) -> llvm::Function * {

  std::vector<llvm::Type *> Doubles{
      Parameters.size(), llvm::Type::getDoubleTy(generator.getContext())};

  auto *FunctionType = llvm::FunctionType::get(
      llvm::Type::getDoubleTy(generator.getContext()), Doubles, false);

  auto *Func =
      llvm::Function::Create(FunctionType, llvm::Function::ExternalLinkage, Id,
                             &generator.getModule());
  int Index = 0;
  for (auto &Arg : Func->args())
    Arg.setName(Parameters[Index++]);

  return Func;
}

auto FuncStatement::codeGen(Generator &generator) -> llvm::Value * {

  auto *Func = generator.getModule().getFunction(Signature->getName());
  if (Func == nullptr)
    Func = Signature->codeGen(generator);

  auto *Block = llvm::BasicBlock::Create(generator.getContext(), "entry", Func);
  generator.getIrBuilder().SetInsertPoint(Block);
  generator.getNamedValues().clear();
  for (llvm::Value &Arg : Func->args())
    generator.getNamedValues().at(Arg.getName().str()) = &Arg;

  llvm::Value *RetVal = Body->codeGen(generator);
  generator.getIrBuilder().CreateRet(RetVal);
  llvm::verifyFunction(*Func);
  return Func;
}

} // namespace thermite