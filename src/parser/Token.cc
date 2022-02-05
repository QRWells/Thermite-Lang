/**
 * @file Token.cc
 * @author QRWells (qirui.wang@moegi.waseda.jp)
 * @brief
 * @version 0.1
 * @date 2022-02-05
 *
 * @copyright Copyright (c) 2021 QRWells. All rights reserved.
 * Licensed under the MIT license.
 *
 */

#include "parser/Token.h"
#include <string>

namespace thermite {
auto Token::getNumber() const -> double { return std::stod(Value); }
auto Token::getClass() const -> enum TokenClass { return TokenClass; }
auto Token::getString() const -> std::string { return Value; }
auto Token::toString() const -> std::string {
  return fmt::format("{{Token: {}, Value: \"{}\"}}", tokenToCstr(TokenClass),
                     Value);
}
auto Token::operator==(enum TokenClass const &tokenClass) -> bool {
  return TokenClass == tokenClass;
}
auto operator<<(std::ostream &output, const Token &token) -> std::ostream & {
  output << token.toString();
  return output;
}
} // namespace thermite