#include "../default_includes.hpp"
#include "../error_handling.hpp"
#include "char_types.hpp"
#include "token_parsing_fucntions.hpp"
#include "tokens.hpp"
#include <array>
#include <cstdint>
#include <format>
#include <fstream>
#include <functional>
#include <optional>

struct TokenPattern {
  std::function<expected<Token, string>(std::ifstream &, uint_fast16_t)>
      function;
  vector<char> start_characters;
  //  I need the next char because some patterns might start with the same char
  //  like: *= and * or + and ++
  optional<char> next_character;

  // If this value is set it will skip calling the function and just give a
  // token with this kind and no value
  optional<TokenKind> fast_parsing_kind;
};
const TokenPattern OTHER_PATTERN = {.fast_parsing_kind = Other};

static std::unordered_map<char, vector<TokenPattern>> TOKEN_PATTERNS_MAP;
expected<TokenPattern, string> find_right_token_pattern(std::ifstream &stream) {
  char first_char = stream.get();

  auto found = TOKEN_PATTERNS_MAP.find(first_char);
  if (found == TOKEN_PATTERNS_MAP.end()) {
    // BAIL_FMT("there were no patterns that: start with '{}' - '{:d}' ",
    //         first_char, first_char)

    stream.putback(first_char);
    return OTHER_PATTERN;
  }
  vector<TokenPattern> right_patterns = found->second;
  for (TokenPattern pattern : right_patterns) {
    bool start_char_match = false;
    for (char start_char : pattern.start_characters) {
      if (start_char == first_char) {
        start_char_match = true;
        break;
      }
    }

    if (pattern.next_character) {
      char next_char = stream.peek();
      if (pattern.next_character.value() != next_char) {
        continue;
      }
    }

    stream.putback(first_char);
    return pattern;
  }

  stream.putback(first_char);

  // BAIL_FMT("there was no right pattern that: starts with "
  //          "'{}' and next character is '{}'",
  //          first_char, stream.peek())

  return OTHER_PATTERN;
}

expected<vector<Token>, string> tokenize_file(string path) {
  std::ifstream file(path); // open file for reading
  if (!file.is_open()) {
    BAIL_FMT("Could not open file at path: {}", path)
  }

  vector<Token> output;
  string line_str;
  uint_fast16_t line_nr = 0;
  while (true) {
    if (file.peek() == 0) {
      break;
    }
    TokenPattern pattern =
        UNWRAP_FMT(find_right_token_pattern(file),
                   "encountered while parsing a line with nr:{}", line_nr);

    if (!file) {
      break;
    }

    if (pattern.fast_parsing_kind) {
      Token token = Token{
          .kind = pattern.fast_parsing_kind.value(),
          .value = "",
          .line = line_nr,
      };
      if (token.kind == NextLine)
        line_nr++;

      file.get();
      if (pattern.next_character != std::nullopt) {
        file.get();
      }
      output.push_back(token);
    } else {

      expected<Token, string> token_result = pattern.function(file, line_nr);
      // TRY_CTX(token_result, "encountered while parsing a token pattern");

      if (token_result.value().kind == NextLine)
        line_nr++;
      output.push_back(token_result.value());
    }
  }

  return output;
}

const std::array<TokenPattern, 55> PATTERNS = {

    TokenPattern{
        .function = handle_number,
        .start_characters = NUMBERS,
    },
    TokenPattern{
        .function = handle_string,
        .start_characters = {'"'},
    },

    TokenPattern{
        .function = handle_compiler_data,
        .start_characters = {'#'},
    },
    TokenPattern{
        .function = handle_comment,
        .start_characters = {'/'},
        .next_character = {'/'},
    },

    TokenPattern{
        .function = handle_identifier,
        .start_characters = SYMBOL_CHARS,
    },

    TokenPattern{
        .start_characters = {' '},
        .fast_parsing_kind = WhiteSpace,
    },
    TokenPattern{
        .start_characters = {'\n'},
        .fast_parsing_kind = NextLine,
    },
    TokenPattern{
        .start_characters = {'+'},
        .fast_parsing_kind = Plus,
    },

    TokenPattern{
        .start_characters = {'+'},
        .next_character{'='},
        .fast_parsing_kind = PlusEquals,
    },

    // --- Group: Brackets and punctuation ---
    TokenPattern{
        .start_characters = {'('},
        .fast_parsing_kind = OpenParen,
    },
    TokenPattern{
        .start_characters = {')'},
        .fast_parsing_kind = CloseParen,
    },
    TokenPattern{
        .start_characters = {'['},
        .fast_parsing_kind = OpenBracket,
    },
    TokenPattern{
        .start_characters = {']'},
        .fast_parsing_kind = CloseBracket,
    },
    TokenPattern{
        .start_characters = {'{'},
        .fast_parsing_kind = OpenCurly,
    },
    TokenPattern{
        .start_characters = {'}'},
        .fast_parsing_kind = CloseCurly,
    },
    TokenPattern{
        .start_characters = {','},
        .fast_parsing_kind = Comma,
    },
    TokenPattern{
        .start_characters = {'.'},
        .fast_parsing_kind = Dot,
    },
    TokenPattern{
        .start_characters = {';'},
        .fast_parsing_kind = SemiColon,
    },
    TokenPattern{
        .start_characters = {':'},
        .fast_parsing_kind = Colon,
    },
    TokenPattern{
        .start_characters = {'-'},
        .next_character = {'>'},
        .fast_parsing_kind = Arrow,
    },
    TokenPattern{
        .start_characters = {'?'},
        .fast_parsing_kind = Question,
    },

    // --- Group: Arithmetic operators ---
    TokenPattern{
        .start_characters = {'+'},
        .fast_parsing_kind = Plus,
    },
    TokenPattern{
        .start_characters = {'-'},
        .fast_parsing_kind = Minus,
    },
    TokenPattern{
        .start_characters = {'*'},
        .fast_parsing_kind = Star,
    },
    TokenPattern{
        .start_characters = {'/'},
        .fast_parsing_kind = Slash,
    },
    TokenPattern{
        .start_characters = {'%'},
        .fast_parsing_kind = Percent,
    },

    // --- Group: Compound assignment ---
    TokenPattern{
        .start_characters = {'+'},
        .next_character = {'='},
        .fast_parsing_kind = PlusEquals,
    },
    TokenPattern{
        .start_characters = {'-'},
        .next_character = {'='},
        .fast_parsing_kind = MinusEquals,
    },
    TokenPattern{
        .start_characters = {'*'},
        .next_character = {'='},
        .fast_parsing_kind = StarEquals,
    },
    TokenPattern{
        .start_characters = {'/'},
        .next_character = {'='},
        .fast_parsing_kind = SlashEquals,
    },

    // --- Group: Increment / Decrement ---
    TokenPattern{
        .start_characters = {'+'},
        .next_character = {'+'},
        .fast_parsing_kind = PlusPlus,
    },
    TokenPattern{
        .start_characters = {'-'},
        .next_character = {'-'},
        .fast_parsing_kind = MinusMinus,
    },

    // --- Group: Comparison operators ---
    TokenPattern{
        .start_characters = {'='},
        .fast_parsing_kind = Equals,
    },
    TokenPattern{
        .start_characters = {'!'},
        .next_character = {'='},
        .fast_parsing_kind = NotEquals,
    },
    TokenPattern{
        .start_characters = {'<'},
        .fast_parsing_kind = Less,
    },
    TokenPattern{
        .start_characters = {'<'},
        .next_character = {'='},
        .fast_parsing_kind = LessEquals,
    },
    TokenPattern{
        .start_characters = {'>'},
        .fast_parsing_kind = Greater,
    },
    TokenPattern{
        .start_characters = {'>'},
        .next_character = {'='},
        .fast_parsing_kind = GreaterEquals,
    },

    // --- Group: Logical operators ---
    TokenPattern{
        .start_characters = {'!'},
        .fast_parsing_kind = Not,
    },
    TokenPattern{
        .start_characters = {'&'},
        .fast_parsing_kind = And,
    },
    TokenPattern{
        .start_characters = {'|'},
        .next_character = {'|'},
        .fast_parsing_kind = Or,
    },

};

void setup_token_patterns() {
  for (TokenPattern pattern : PATTERNS)
    for (char key : pattern.start_characters) {
      TOKEN_PATTERNS_MAP[key].push_back(pattern);
    }
}
