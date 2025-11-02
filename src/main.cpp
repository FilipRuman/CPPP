#include "default_includes.hpp"
#include "lexer/lexer.hpp"
#include <format>
#include <iostream>
#include <string>

optional<vector<Token>> tokenize(string path) {
  expected<vector<Token>, string> tokenization_output = tokenize_file(path);

  if (!tokenization_output) {
    string to_add = format_error_string(std::format(
        "|encountered during tokenization of file at path: '{}'", path));
    string final_message = add_context_to_error(to_add, tokenization_output);
    std::cout << std::format("\033[31mERROR: \n{}\033[0m", final_message);
    return std::nullopt;
  }
  std::cout << "TOKENS:\n";
  for (Token token : tokenization_output.value()) {
    std::cout << token.to_string() << "\n";
  }
  return tokenization_output.value();
}

// this is not the most efficient way but it is a clean one
vector<Token> blacklist_filter_tokens(vector<Token> tokens,
                                      unordered_set<TokenKind> black_list) {
  vector<Token> out(tokens.size());
  for (Token token : tokens) {
    if (!black_list.contains(token.kind))
      out.push_back(token);
  }
  return out;
}

int main() {
  setup_token_patterns();
  auto tokens = tokenize("../test_file.c");
  if (!tokens) {
    return 1;
  }
  unordered_set<TokenKind> blacklist = {TokenKind::WhiteSpace,
                                        TokenKind::NextLine, TokenKind::Other,
                                        TokenKind::Comment};
  vector<Token> filtered = blacklist_filter_tokens(tokens.value(), blacklist);

  return 0;
}
