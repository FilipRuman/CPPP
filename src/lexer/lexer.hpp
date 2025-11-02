#pragma once
#include "tokens.hpp"
void setup_token_patterns();
expected<vector<Token>, string> tokenize_file(string path);
