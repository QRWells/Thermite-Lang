/**
 * @file AstNode.cc
 * @author QRWells (qirui.wang@moegi.waseda.jp)
 * @brief
 * @version 0.1
 * @date 2021-12-19
 *
 * @copyright Copyright (c) 2021 QRWells. All rights reserved.
 * Licensed under the MIT license.
 *
 */

#include "ast/AstNode.h"

namespace thermite {
auto AstNode::codeGen(const CodeGenContext &context) -> llvm::Value * {
  return nullptr;
}
} // namespace thermite
