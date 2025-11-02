module;
#include "../default_includes.hpp"
#include <array>
#include <functional>
export module Lookup;

struct Parser;
struct Expression;

export struct TokenKindParsingStats {
  std::function<expected<Expression, string>(Parser)> nod_function;
  std::function<expected<Expression, string>(Parser, int, Expression)>
      led_function;
  int binding_power;
};

const std::array<TokenKindParsingStats, 59> TOKEN_PARSING_STATS = {
    // Tab,
    // WhiteSpace,
    // NextLine,
    // Comment,
    // EndOfFile,
    // CompilerData,
    // OpenParen,
    // CloseParen,
    // OpenBracket,
    // CloseBracket,
    // OpenCurly,
    // CloseCurly,
    // Comma,
    // Dot,
    // SemiColon,
    // Colon,
    // Arrow,
    // Question,
    // Plus,
    // Minus,
    // Star,
    // Slash,
    // Percent,
    // PlusEquals,
    // MinusEquals,
    // StarEquals,
    // SlashEquals,
    // PlusPlus,
    // MinusMinus,
    // Equals,
    // NotEquals,
    // Less,
    // LessEquals,
    // Greater,
    // GreaterEquals,
    // Not,
    // And,
    // Or,
    // BitwiseShiftLeft,
    // BitwiseShiftRight,
    // Assignment,
    // Reference,
    // Number,
    // String,
    // True,
    // False,
    // Identifier,
    // Static,
    // Return,
    // If,
    // Else,
    // While,
    // For,
    // New,
    // Pub,
    // Import,
    // Enum,
    // Struct,
    // Break,
    // Other,
};
