#pragma once
#include "../default_includes.hpp"
#include <format>
#include <string>
enum TokenKind {
  Tab,
  WhiteSpace,
  NextLine,
  Comment,
  EndOfFile,
  CompilerData,

  OpenParen,
  CloseParen,
  OpenBracket,
  CloseBracket,
  OpenCurly,
  CloseCurly,
  Comma,
  Dot,
  SemiColon,
  Colon,
  Arrow,
  Question,

  Plus,
  Minus,
  Star,
  Slash,
  Percent,

  PlusEquals,
  MinusEquals,
  StarEquals,
  SlashEquals,

  PlusPlus,
  MinusMinus,

  Equals,
  NotEquals,
  Less,
  LessEquals,
  Greater,
  GreaterEquals,

  Not,
  And,
  Or,

  BitwiseShiftLeft,
  BitwiseShiftRight,

  Assignment,
  Reference,

  Number,
  String,
  True,
  False,

  Identifier,
  Static,
  Return,
  If,
  Else,
  While,
  For,
  New,
  Pub,
  Import,
  Enum,
  Struct,
  Break,
  Other,
};
const string token_kind_to_string(TokenKind kind);
struct Token {
public:
  TokenKind kind;
  string value;
  uint_fast16_t line; // needed for better debugging
  const string to_string();
};
