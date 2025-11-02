#pragma once

#include "../default_includes.hpp"
#include "tokens.hpp"
#include <fstream>
expected<Token, string> handle_string(std::ifstream &stream,
                                      uint_fast16_t line);
expected<Token, string> handle_compiler_data(std::ifstream &stream,
                                             uint_fast16_t line);

expected<Token, string> handle_number(std::ifstream &stream,
                                      uint_fast16_t line);
expected<Token, string> handle_identifier(std::ifstream &stream,
                                          uint_fast16_t line);

expected<Token, string> handle_comment(std::ifstream &stream,
                                       uint_fast16_t line);
