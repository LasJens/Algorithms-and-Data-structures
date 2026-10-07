#include "tokenize.h"

std::vector<Token> Tokenize(const std::string_view& string) {
  std::vector<Token> tokens;
  std::string cur_token;
  for (size_t i = 0; i <= string.size(); ++i) {
    if (i == string.size() || string[i] == ' ') {
      if (!cur_token.empty()) {
        if (cur_token == "+") {
          tokens.emplace_back(PlusToken());
        } else if (cur_token == "-") {
          tokens.emplace_back(MinusToken());
        } else if (cur_token == "*") {
          tokens.emplace_back(MultiplyToken());
        } else if (cur_token == "/") {
          tokens.emplace_back(DivideToken());
        } else if (cur_token == "%") {
          tokens.emplace_back(ResidualToken());
        } else if (cur_token == "(") {
          tokens.emplace_back(OpeningBracketToken());
        } else if (cur_token == ")") {
          tokens.emplace_back(ClosingBracketToken());
        } else if (cur_token == "sqr") {
          tokens.emplace_back(SqrToken());
        } else if (cur_token == "max") {
          tokens.emplace_back(MaxToken());
        } else if (cur_token == "min") {
          tokens.emplace_back(MinToken());
        } else if (cur_token == "abs") {
          tokens.emplace_back(AbsToken());
        } else {
          int64_t number = 0;
          bool number_flag = true;
          bool negative_flag = false;
          int64_t index = 0;
          if (cur_token.size() > 1) {
            if (cur_token[0] == '+') {
              index = 1;
            } else if (cur_token[0] == '-') {
              negative_flag = true;
              index = 1;
            }
          }
          for (size_t j = index; j < cur_token.size(); ++j) {
            if ((0 <= cur_token[j] - '0') && (cur_token[j] - '0' <= 9)) {
              number = number * 10 + cur_token[j] - '0';
            } else {
              number_flag = false;
              break;
            }
          }
          if (number_flag) {
            if (negative_flag) {
              number *= -1;
            }
            tokens.emplace_back(NumberToken{number});
          } else {
            tokens.emplace_back(UnknownToken{cur_token});
          }
        }
      }
      cur_token = "";
    } else {
      cur_token += string[i];
    }
  }
  return tokens;
}
