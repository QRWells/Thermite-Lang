/**
 * @file Operation.h
 * @author QRWells (qirui.wang@moegi.waseda.jp)
 * @brief
 * @version 0.1
 * @date 2022-02-05
 *
 * @copyright Copyright (c) 2021 QRWells. All rights reserved.
 * Licensed under the MIT license.
 *
 */

#pragma once
#ifndef THERMITE_LANG_ENUM_OPERATION
#define THERMITE_LANG_ENUM_OPERATION

namespace thermite {
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
  NotEqual = '!' + 20,

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
#endif