module;
#include "../default_includes.hpp"
export module Expression;
import Parser;
import Lookup;

struct DebugData {
  uint_fast16_t line;
};
export struct Expression {
  DebugData debug_data;
  virtual ~Expression() = default; // needed for polymorphism
};

struct Expression_Identifier : Expression {
  DebugData debug_data;
  string name;
  Expression_Identifier(string name, DebugData debug_data)
      : name(name), debug_data(debug_data) {}
};

struct Number : Expression {
  string name;
};

expected<Expression, string> parse_expression(Parser parser, int binding_power);

void test(Expression expr) {
  std::vector<std::unique_ptr<Expression>> expressions;

  DebugData dbg;

  expressions.push_back(std::make_unique<Expression_Identifier>("s", dbg));
}

expected<Expression, string> parse_expression(Parser parser,
                                              int binding_power) {
  Token current_token = parser.current_token();
  TokenKindParsingStats current_stats = TOKEN_PARSING_STATS[current_token.kind];

  Expression current_expr = UNWRAP(current_stats.nod_function(parser));

  current_stats = parser.current_stats();
  while (current_stats.binding_power > binding_power) {
    current_expr = UNWRAP(current_stats.led_function(
        parser, current_stats.binding_power, current_expr));

    current_stats = parser.current_stats();
  }
  return current_expr;
}
