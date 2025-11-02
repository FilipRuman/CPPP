
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>
const std::vector<char> SYMBOL_CHARS = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B',
    'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '_',
};

const std::unordered_set<char> VALID_IDENTIFIER_TOKEN_CHARS = {

    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c',
    'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C',
    'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '_',
};
const std::vector<char> NUMBERS = {'0', '1', '2', '3', '4',
                                   '5', '6', '7', '8', '9'};
const std::unordered_set<char> VALID_NUMBER_TOKEN_CHARS = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8',
    '9', 'x', 'a', 'b', 'c', 'd', 'e', 'f',
};
