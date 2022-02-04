/**
 * @file Generator.cc
 * @author QRWells (qirui.wang@moegi.waseda.jp)
 * @brief
 * @version 0.1
 * @date 2021-12-19
 *
 * @copyright Copyright (c) 2021 QRWells. All rights reserved.
 * Licensed under the MIT license.
 *
 */

#include "parser/Generator.h"

namespace thermite {
Generator::Generator()
    : GIrBuilder(GLlvmContext), GModule(R"(Thermite)", GLlvmContext) {}
} // namespace thermite
