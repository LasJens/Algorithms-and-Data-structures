#ifndef TOKENIZE_H
#define TOKENIZE_H

#include <variant>
#include <string>
#include <string_view>
#include <vector>

struct PlusToken {};

struct MinusToken {};

struct MultiplyToken {};

struct DivideToken {};

struct ResidualToken {};

struct OpeningBracketToken {};

struct ClosingBracketToken {};

struct SqrToken {};

struct MaxToken {};

struct MinToken {};

struct AbsToken {};

struct NumberToken {
  int64_t value;
};

struct UnknownToken {
  std::string value;
};

bool inline operator==(const PlusToken&, const PlusToken&) {
  return true;
}

bool inline operator==(const MinusToken&, const MinusToken&) {
  return true;
}

bool inline operator==(const MultiplyToken&, const MultiplyToken&) {
  return true;
}

bool inline operator==(const DivideToken&, const DivideToken&) {
  return true;
}

bool inline operator==(const ResidualToken&, const ResidualToken&) {
  return true;
}

bool inline operator==(const OpeningBracketToken&, const OpeningBracketToken&) {
  return true;
}

bool inline operator==(const ClosingBracketToken&, const ClosingBracketToken&) {
  return true;
}

bool inline operator==(const SqrToken&, const SqrToken&) {
  return true;
}

bool inline operator==(const MaxToken&, const MaxToken&) {
  return true;
}

bool inline operator==(const MinToken&, const MinToken&) {
  return true;
}

bool inline operator==(const AbsToken&, const AbsToken&) {
  return true;
}

bool inline operator==(const NumberToken& first, const NumberToken& second) {
  return first.value == second.value;
}

bool inline operator==(const UnknownToken& first, const UnknownToken& second) {
  return first.value == second.value;
}

using Token = std::variant<PlusToken, MinusToken, MultiplyToken, DivideToken, ResidualToken, OpeningBracketToken,
                           ClosingBracketToken, SqrToken, MaxToken, MinToken, AbsToken, NumberToken, UnknownToken>;

std::vector<Token> Tokenize(const std::string_view&);

#endif
