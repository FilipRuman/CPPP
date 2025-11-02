module;
export module Parser;
#include "../default_includes.hpp"
import Lookup;

export struct Parser {
public:
  vector<Token> tokens;
  uint_fast16_t current_token_index;

  Token advance() {
    current_token_index++;
    return tokens[current_token_index - 1];
  }

  Token current_token() { return tokens[current_token_index]; }

  expected<Token, string> expect(TokenKind kind) {
    Token current = advance();
    if (current.kind == kind) {
      BAIL_FMT("expected: {}, found: {}", token_kind_to_string(kind),
               current.to_string());
    }
    return current;
  }

  TokenKindParsingStats current_stats() {
    return TOKEN_PARSING_STATS[tokens[current_token_index]];
  }

  int current_binding_power() {
    return TOKEN_PARSING_STATS[tokens[current_token_index]].binding_power;
  }
};

vector<Expression> parse(vector<Token> tokens) {
  vector<Expression> out;
  Parser parser{.tokens = tokens, .current_token_index = 0};
  while (parser.current_token_index != tokens.size()) {
    parse_expression(parser, 0);
  }
}
