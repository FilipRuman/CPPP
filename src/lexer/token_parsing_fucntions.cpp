#include "../default_includes.hpp"
#include "char_types.hpp"
#include "tokens.hpp"
#include <cstdint>
#include <fstream>
#include <iostream>

expected<char, string> expect(std::ifstream &stream, char expected_character) {
  auto to_check = stream.get();
  if (to_check != expected_character) {
    BAIL_FMT("expected to get: '{}', found '{}'", expected_character, to_check);
  }
  return to_check;
}

expected<Token, string> handle_string(std::ifstream &stream,
                                      uint_fast16_t line) {

  TRY(expect(stream, '"'));
  string value;
  char current_char;
  while (true) {
    current_char = stream.get();
    if (current_char == '"') {
      break;
    }
    value += current_char;
  }

  return Token{.kind = TokenKind::String, .value = value, .line = line};
}

expected<Token, string> handle_number(std::ifstream &stream,
                                      uint_fast16_t line) {

  string value;
  char current_char;
  while (true) {
    current_char = stream.get();
    if (!VALID_NUMBER_TOKEN_CHARS.contains(current_char)) {
      break;
    }
    value += current_char;
  }

  return Token{.kind = TokenKind::Number, .value = value, .line = line};
}
expected<Token, string> handle_identifier(std::ifstream &stream,
                                          uint_fast16_t line) {
  string value;
  char current_char;
  while (true) {
    current_char = stream.get();
    if (!VALID_IDENTIFIER_TOKEN_CHARS.contains(current_char)) {
      stream.putback(current_char);
      break;
    }
    value += current_char;
  }

  return Token{.kind = TokenKind::Identifier, .value = value, .line = line};
}

expected<Token, string> handle_compiler_data(std::ifstream &stream,
                                             uint_fast16_t line) {

  TRY(expect(stream, '#'));

  string value;
  char current_char;
  while (true) {
    current_char = stream.get();
    if (current_char == '\n') {
      break;
    }
    value += current_char;
  }

  return Token{.kind = TokenKind::CompilerData, .value = value, .line = line};
}

expected<Token, string> handle_comment(std::ifstream &stream,
                                       uint_fast16_t line) {
  TRY(expect(stream, '/'));
  TRY(expect(stream, '/'));

  string value;
  char current_char;
  while (true) {
    current_char = stream.get();
    if (current_char == '\n') {
      break;
    }
    value += current_char;
  }

  return Token{.kind = TokenKind::Comment, .value = value, .line = line};
}
