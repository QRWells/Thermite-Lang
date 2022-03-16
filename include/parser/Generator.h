/**
 * @file Generator.h
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
#ifndef THERMITE_LANG_GENERATOR
#define THERMITE_LANG_GENERATOR

#include <map>
#include <string>

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
class Generator {
public:
  Generator();
  ~Generator() = default;

  auto getContext() -> llvm::LLVMContext &;
  auto getNamedValues() -> std::map<std::string, llvm::Value *> &;
  auto getIrBuilder() -> llvm::IRBuilder<> &;
  auto getModule() -> llvm::Module &;

private:
  llvm::LLVMContext LlvmContext;

  llvm::IRBuilder<> IrBuilder;

  llvm::Module Module;

  std::map<std::string, llvm::Value *> NamedValues;
};
} // namespace thermite

#endif // !THERMITE_LANG_GENERATOR
