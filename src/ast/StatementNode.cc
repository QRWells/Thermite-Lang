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
namespace thermite {
auto VarDefStatement::codeGen(CodeGenContext const &code_gen_context)
    -> llvm::Value * {
  return StatementNode::codeGen(code_gen_context);
}

auto FuncStatement::codeGen(CodeGenContext const &code_gen_context)
    -> llvm::Value * {
  return StatementNode::codeGen(code_gen_context);
}

} // namespace thermite