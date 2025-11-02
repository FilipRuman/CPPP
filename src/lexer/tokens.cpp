#include "tokens.hpp"
#include "../default_includes.hpp"
#include <sys/types.h>
const string Token::to_string() {
  return std::format("{{kind: {}, value: {}, line: {}}}",
                     token_kind_to_string(kind), value, line);
}
const string token_kind_to_string(TokenKind kind) {
  switch (kind) {
  case TokenKind::Tab:
    return "Tab";
  case TokenKind::WhiteSpace:
    return "WhiteSpace";
  case TokenKind::NextLine:
    return "NextLine";
  case TokenKind::Comment:
    return "Comment";
  case TokenKind::EndOfFile:
    return "EndOfFile";
  case TokenKind::CompilerData:
    return "CompilerData";

  case TokenKind::OpenParen:
    return "OpenParen";
  case TokenKind::CloseParen:
    return "CloseParen";
  case TokenKind::OpenBracket:
    return "OpenBracket";
  case TokenKind::CloseBracket:
    return "CloseBracket";
  case TokenKind::OpenCurly:
    return "OpenCurly";
  case TokenKind::CloseCurly:
    return "CloseCurly";
  case TokenKind::Comma:
    return "Comma";
  case TokenKind::Dot:
    return "Dot";
  case TokenKind::SemiColon:
    return "SemiColon";
  case TokenKind::Colon:
    return "Colon";
  case TokenKind::Arrow:
    return "Arrow";
  case TokenKind::Question:
    return "Question";

  case TokenKind::Plus:
    return "Plus";
  case TokenKind::Minus:
    return "Minus";
  case TokenKind::Star:
    return "Star";
  case TokenKind::Slash:
    return "Slash";
  case TokenKind::Percent:
    return "Percent";

  case TokenKind::PlusEquals:
    return "PlusEquals";
  case TokenKind::MinusEquals:
    return "MinusEquals";
  case TokenKind::StarEquals:
    return "StarEquals";
  case TokenKind::SlashEquals:
    return "SlashEquals";

  case TokenKind::PlusPlus:
    return "PlusPlus";
  case TokenKind::MinusMinus:
    return "MinusMinus";

  case TokenKind::Equals:
    return "Equals";
  case TokenKind::NotEquals:
    return "NotEquals";
  case TokenKind::Less:
    return "Less";
  case TokenKind::LessEquals:
    return "LessEquals";
  case TokenKind::Greater:
    return "Greater";
  case TokenKind::GreaterEquals:
    return "GreaterEquals";

  case TokenKind::Not:
    return "Not";
  case TokenKind::And:
    return "And";
  case TokenKind::Or:
    return "Or";

  case TokenKind::BitwiseShiftLeft:
    return "BitwiseShiftLeft";
  case TokenKind::BitwiseShiftRight:
    return "BitwiseShiftRight";

  case TokenKind::Assignment:
    return "Assignment";
  case TokenKind::Reference:
    return "Reference";

  case TokenKind::Number:
    return "Number";
  case TokenKind::String:
    return "String";
  case TokenKind::True:
    return "True";
  case TokenKind::False:
    return "False";

  case TokenKind::Identifier:
    return "Identifier";
  case TokenKind::Static:
    return "Static";
  case TokenKind::Return:
    return "Return";
  case TokenKind::If:
    return "If";
  case TokenKind::Else:
    return "Else";
  case TokenKind::While:
    return "While";
  case TokenKind::For:
    return "For";
  case TokenKind::New:
    return "New";
  case TokenKind::Pub:
    return "Pub";
  case TokenKind::Import:
    return "Import";
  case TokenKind::Enum:
    return "Enum";
  case TokenKind::Struct:
    return "Struct";
  case TokenKind::Break:
    return "Break";
  case TokenKind::Other:
    return "Other";
  }
  return "<unknown>";
}
